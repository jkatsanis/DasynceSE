#include "Game.h"

void Game::Start()
{
	const std::string scene_name = "scene 1";

	this->m_Player = spe::PrefabRepository::GetPrefabByName("Player");

	this->EngineConfig.ptr_Sprites->Add(this->m_Player);

	this->EngineConfig.SetNoDeleteOnSceneSwap(this->m_Player);

	this->m_PlayerController.Start(this->EngineConfig);

	this->StartScene(scene_name);
}

void Game::StartScene(const std::string& scene)
{
	this->EngineConfig.LoadScene(scene);

	this->m_Camera.Start(this->EngineConfig.ptr_Camera, this->m_Player);

	if (this->EngineConfig.ptr_SceneHandler->CurrentScene == "scene 1")
	{
		this->m_LevelUI.Start(this->EngineConfig);
	}

	if(this->EngineConfig.ptr_SceneHandler->CurrentScene == "computer_room")
	{
		this->m_ComputerRoom.Start(this->EngineConfig);
	}
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
	if (sceneName == "computer_room")
	{
		this->m_PlayerController.GetPlayer()->Transform.Teleport(COMPUTER_ROOM_TP_POSITION);
	}
	else if (sceneName == "scene 1")
	{
		this->m_PlayerController.GetPlayer()->Transform.Teleport(KANAL_TP_POSITION);
	}
	this->StartScene(sceneName);
}
