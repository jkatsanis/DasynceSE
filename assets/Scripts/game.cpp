#include "Game.h"

void Game::Start()
{
	this->m_PlayerController.Start(this->EngineConfig);
	this->m_LevelUI.Start(this->EngineConfig);
}

void Game::Update()
{	
	std::string fps = "FPS: " + std::to_string(spe::Time::s_fps);
	ImGui::Text(fps.c_str());

	// Movement
	this->m_PlayerController.Update();

	// UI
	this->m_LevelUI.Update();
}
