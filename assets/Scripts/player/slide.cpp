#include "slide.h"

// Private

void Slide::animationControl(const bool& is_walking)
{
	if (this->slideCondition(is_walking))
	{
		this->m_ptr_player->animator.stop("runv2");
		this->m_ptr_player->animator.play("dash");
	}
}

bool Slide::slideCondition(const bool& is_walking)
{
	bool a = s2d::Input::onKeyHold(s2d::KeyBoardCode::A) && !s2d::Input::onKeyHold(s2d::KeyBoardCode::D);
	bool b = !s2d::Input::onKeyHold(s2d::KeyBoardCode::A) && s2d::Input::onKeyHold(s2d::KeyBoardCode::D);

	bool ad = s2d::Input::onKeyHold(s2d::KeyBoardCode::A);
	bool da = s2d::Input::onKeyHold(s2d::KeyBoardCode::D);

	return (s2d::Input::onKeyPress(s2d::KeyBoardCode::LShift) && is_walking
		&& (a || b));
}

bool Slide::controlWalkCondition(s2d::KeyBoardCode direction)
{
	DashKey right = (direction == s2d::KeyBoardCode::A) ? DashKey::D : DashKey::A;

	DashKey left = (direction == s2d::KeyBoardCode::A) ? DashKey::A : DashKey::D;

	if (this->m_dash_key == left)
	{
		return true;
	}
	if (this->m_dash_key == right)
	{
		this->stop();
	}
	return false;
}


// Public 

void Slide::start(s2d::Sprite* player)
{
	this->m_ptr_player = player;

	this->m_slide_time = this->m_ptr_player->animator.animations["dash"].getAnimationTime() / 100;

	this->m_time_slided = 0.0f;
}

void Slide::update(const bool& is_walking)
{
	this->animationControl(is_walking);

	bool ad = s2d::Input::onKeyHold(s2d::KeyBoardCode::A);

	if (this->slideCondition(is_walking))
	{
		this->m_ptr_player->physicsBody.velocity.x = 0;
		const float direction = (this->m_ptr_player->transform.getScale().x < 0.0f) ? -1.0f : 1.0f;
		s2d::Physics::addForce(this->m_ptr_player, s2d::Vector2(direction, 0), 3000.0f);
		this->m_sliding = true;

		this->m_dash_key = (ad) ? DashKey::A : DashKey::D;

	}
	if (this->m_sliding)
	{
		this->m_ptr_player->physicsBody.velocity.y = 0;
		this->m_time_slided += s2d::Time::s_delta_time;
		if (this->m_time_slided >= this->m_slide_time)
		{
			this->stop();
		}
	}
}

void Slide::stop()
{
	this->m_ptr_player->physicsBody.velocity.x = 0.0f;
	this->m_sliding = false;
	this->m_time_slided = 0.0f;

	this->m_ptr_player->animator.stop("dash");
	this->m_ptr_player->animator.play("runv2");

	// Walkk true
	this->m_dash_key = DashKey::None;
}
