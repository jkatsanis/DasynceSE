#include "Slide.h"

// Private

void Slide::animationControl(const bool& is_walking)
{
	if (this->slideCondition(is_walking))
	{
		this->m_ptr_player->Animator.Stop("runv2");
		this->m_ptr_player->Animator.Play("dash");
	}
}

bool Slide::slideCondition(const bool& is_walking)
{
	bool a = spe::Input::OnKeyHold(spe::KeyBoardCode::A) && !spe::Input::OnKeyHold(spe::KeyBoardCode::D);
	bool b = !spe::Input::OnKeyHold(spe::KeyBoardCode::A) && spe::Input::OnKeyHold(spe::KeyBoardCode::D);

	bool ad = spe::Input::OnKeyHold(spe::KeyBoardCode::A);
	bool da = spe::Input::OnKeyHold(spe::KeyBoardCode::D);

	return (spe::Input::OnKeyPress(spe::KeyBoardCode::LShift) && is_walking
		&& (a || b));
}

bool Slide::controlWalkCondition(spe::KeyBoardCode direction)
{
	DashKey right = (direction == spe::KeyBoardCode::A) ? DashKey::D : DashKey::A;

	DashKey left = (direction == spe::KeyBoardCode::A) ? DashKey::A : DashKey::D;

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

void Slide::start(spe::Sprite* player)
{
	this->m_ptr_player = player;

	this->m_slide_time = this->m_ptr_player->Animator.Animations["dash"].GetAnimationTime() / 100;

	this->m_time_slided = 0.0f;
	this->m_sliding = false;
}

void Slide::update(const bool& is_walking)
{
	this->animationControl(is_walking);

	bool ad = spe::Input::OnKeyHold(spe::KeyBoardCode::A);

	if (this->slideCondition(is_walking))
	{
		this->m_ptr_player->Physicsbody.Velocity.X = 0;
		const float direction = (this->m_ptr_player->Transform.GetScale().X < 0.0f) ? -1.0f : 1.0f;
		spe::Physics::AddForce(this->m_ptr_player, spe::Vector2(direction, 0), SLIDE_FORCE);
		this->m_sliding = true;

		this->m_dash_key = (ad) ? DashKey::A : DashKey::D;

	}
	if (this->m_sliding)
	{
		this->m_ptr_player->Physicsbody.Velocity.Y = 0;
		this->m_time_slided += spe::Time::s_DeltaTime;
		if (this->m_time_slided >= this->m_slide_time)
		{
			this->stop();
		}
	}
}

void Slide::stop()
{
	this->m_ptr_player->Physicsbody.Velocity.X = 0.0f;
	this->m_sliding = false;
	this->m_time_slided = 0.0f;

	this->m_ptr_player->Animator.Stop("dash");

	if (spe::Input::OnKeyHold(spe::KeyBoardCode::A) || spe::Input::OnKeyHold(spe::KeyBoardCode::D))
	{
		this->m_ptr_player->Animator.Play("runv2");
	}
	else
	{
		this->m_ptr_player->Animator.Play("idle");
	}


	// Walkk true
	this->m_dash_key = DashKey::None;
}