#include "game.h"

void Game::start()
{
	this->config.ptr_sprites->getSpriteWithName("SmokeBig")->animator.play("smoke");
	this->m_controller.start(*this);
}

void Game::update()
{	
	this->m_controller.update();
}
