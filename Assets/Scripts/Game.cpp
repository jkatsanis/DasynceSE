#include "Game.h"

void Game::Start()
{
	this->StartScene("scene 1");
}

void Game::StartScene(const std::string& scene)
{
	this->EngineConfig.ptr_SceneHandler->LoadScene(scene, *this->EngineConfig.ptr_Camera, *this->EngineConfig.ptr_BackgroundColor);

	if (this->EngineConfig.ptr_SceneHandler->CurrentScene == "scene 1")
	{
		this->m_LevelUI.Start(this->EngineConfig);
	}

	if(this->EngineConfig.ptr_SceneHandler->CurrentScene == "computer_room")
	{
		this->m_ComputerRoom.Start(this->EngineConfig);
	}

	this->m_PlayerController.Start(this->EngineConfig);
	this->m_Camera.Start(this->EngineConfig.ptr_Camera, this->m_PlayerController.GetPlayer());
}

void Game::Update()
{	
	std::string fps = "FPS: " + std::to_string(spe::Time::s_FPS);
	ImGui::Text(fps.c_str());

	// Movement
	this->m_PlayerController.Update();

	// Cmaera
	this->m_Camera.Update();

	if (this->EngineConfig.ptr_SceneHandler->CurrentScene == "scene 1")
	{
		// UI
		this->m_LevelUI.Update([this](const std::string& sceneName) {
			this->OnSceneChange(sceneName);
		});
	}
	if (this->EngineConfig.ptr_SceneHandler->CurrentScene == "computer_room")
	{
		this->m_ComputerRoom.Update([this](const std::string& sceneName) {
			this->OnSceneChange(sceneName);
		});
	}
}

void Game::OnSceneChange(const std::string& sceneName)
{
	spe::Sprite* player = this->EngineConfig.ptr_Sprites->GetByName("Player");
	spe::Sprite* copy = new spe::Sprite(*player);

	this->EngineConfig.ptr_SceneHandler->LoadScene(sceneName, *this->EngineConfig.ptr_Camera, *this->EngineConfig.ptr_BackgroundColor);

	copy->Name = "Player";
	this->EngineConfig.ptr_Sprites->Add(copy);

	if (this->EngineConfig.ptr_SceneHandler->CurrentScene == "scene 1")
	{
		this->m_LevelUI.Start(this->EngineConfig);
	}

	if (this->EngineConfig.ptr_SceneHandler->CurrentScene == "computer_room")
	{
		this->m_ComputerRoom.Start(this->EngineConfig);
	}

	this->m_PlayerController.Start(this->EngineConfig);
	this->m_Camera.Start(this->EngineConfig.ptr_Camera, this->m_PlayerController.GetPlayer());

	copy->Transform.Teleport(spe::Vector2(0, 0));
}
