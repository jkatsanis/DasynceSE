#include "wallJump.h"

void WallJump::start(s2d::Sprite* player)
{
	this->m_ptr_player = player;
}

void WallJump::update(const bool& is_grounded)
{
	if (this->m_ptr_player->collider.collidedWithTag("wall") != nullptr && s2d::Input::onKeyHold(s2d::KeyBoardCode::A))
	{
		this->m_ptr_player->physicsBody.velocity.y = this->m_wall_velocity;
		this->m_on_wall = true;

	}

	if (!this->m_on_wall)
	{
		return;
	}

	this->m_wall_timer += s2d::Time::s_delta_time;

	if (this->m_wall_timer >= WALL_SLIDE_TIME)
	{
		this->m_wall_velocity--;
	}

	if (is_grounded)
	{
		this->m_wall_velocity = 0;
		this->m_wall_timer = 0;
		this->m_on_wall = false;
	}
}
