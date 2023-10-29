#include "game.h"

void Game::start()
{
	this->config.ptr_sprites->getSpriteWithName("SmokeBig")->animator.play("smoke");
	this->config.ptr_sprites->getSpriteWithName("SmokeSmall")->animator.play("smoke_small");
	this->m_controller.start(*this);
}

void Game::update()
{	
	ImGui::Text(std::to_string(s2d::Time::fps).c_str());
	this->m_controller.update();
}
