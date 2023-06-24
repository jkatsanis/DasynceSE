#include "playerController.h"

#include <game.h>

void PlayerController::start(Game& game)
{
	this->m_grounded = false;
	this->m_game = &game;
	this->m_ptr_player = game.config.ptr_sprites->getSpriteWithName("Player");
	this->m_scale = this->m_ptr_player->transform.getScale();
}

void PlayerController::update()
{
	this->movement();
}

void PlayerController::movement()
{
	if (s2d::Input::onKeyPress(s2d::KeyBoardCode::A) || s2d::Input::onKeyPress(s2d::KeyBoardCode::D))
	{
		this->m_ptr_player->animator.play("run");
	}
	else if ((s2d::Input::onKeyRelease(s2d::KeyBoardCode::A) || s2d::Input::onKeyRelease(s2d::KeyBoardCode::D))
		&& !s2d::Input::onKeyHold(s2d::KeyBoardCode::A) && !s2d::Input::onKeyHold(s2d::KeyBoardCode::D))
	{
		this->m_ptr_player->animator.stop("run");
	}

	if (s2d::Input::onKeyHold(s2d::KeyBoardCode::A))
	{
		this->m_ptr_player->transform.setScale(s2d::Vector2(-this->m_scale.x, this->m_scale.y));
		this->m_ptr_player->transform.position.x -= PLAYER_SPEED * s2d::Time::s_delta_time;
	}
	if (s2d::Input::onKeyHold(s2d::KeyBoardCode::D))
	{
		this->m_ptr_player->transform.setScale(s2d::Vector2(this->m_scale.x, this->m_scale.y));
		this->m_ptr_player->transform.position.x += PLAYER_SPEED * s2d::Time::s_delta_time;
	}
	if (s2d::Input::onKeyPress(s2d::KeyBoardCode::Space) && this->m_grounded)
	{
		this->m_grounded = false;
		this->m_ptr_player->physicsBody.velocity.y = 0;
		s2d::Physics::addForce(this->m_ptr_player, s2d::Vector2(0, 1), 1000.0f);
	}
	if (this->m_ptr_player->collider.colliding_sprite != nullptr)
	{
		if (this->m_ptr_player->collider.colliding_sprite->parent != nullptr
			&& this->m_ptr_player->collider.colliding_sprite->parent->name == "FloorContainer")
		{
			this->m_grounded = true;
		}
	}

	s2d::GameObject::camera.transform.position = s2d::Vector2(this->m_ptr_player->transform.position.x, this->m_ptr_player->transform.position.y + 170);
}

