#include "game.h"

void Game::start()
{
	this->m_controller.start(*this);
}

void Game::update()
{	
	this->m_controller.update();

	if (s2d::Input::onKeyPress(s2d::KeyBoardCode::M))
	{
		s2d::GameObject::camera.setZoom(s2d::GameObject::camera.getZoom() + 200 * s2d::Time::s_delta_time);
	}
}
