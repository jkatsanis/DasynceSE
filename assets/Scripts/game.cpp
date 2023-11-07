#include "game.h"

void Game::start()
{
	this->m_controller.start(*this);
}

void Game::update()
{	
	this->m_controller.update();
}
