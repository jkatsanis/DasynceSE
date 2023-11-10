#include "game.h"

void Game::start()
{
	this->m_controller.start(*this);
	this->m_controller_cam.start(this->m_controller.getPlayer());
	//this->m_enemy_behaviour.start(this->config);
}

void Game::update()
{	
	std::string fps = std::to_string(s2d::Time::fps);
	ImGui::Text(fps.c_str());

	this->m_controller.update();
	this->m_controller_cam.update();
	//this->m_enemy_behaviour.update();
}
