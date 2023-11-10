#include "game.h"

void Game::start()
{
	this->m_controller.start(*this);
	this->m_controller_cam.start(this->m_controller.getPlayer());
}

void Game::update()
{	
	std::string fps = std::to_string(s2d::Time::fps);
	ImGui::MenuItem(fps.c_str());
	this->m_controller.update();
	this->m_controller_cam.update();
}
