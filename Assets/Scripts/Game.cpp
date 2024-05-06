#include "Game.h"

void Game::Start()
{
	const std::string scene_name = "scene 1";
	this->EngineConfig.ptr_SceneHandler->LoadScene(scene_name, *this->EngineConfig.ptr_Camera, *this->EngineConfig.ptr_BackgroundColor);

	this->m_PlayerController.Start(this->EngineConfig);
	this->m_Camera.Start(this->EngineConfig.ptr_Camera, this->m_PlayerController.GetPlayer());


	this->StartScene(scene_name);

	spe::Sprite* player = this->EngineConfig.ptr_Sprites->GetByName("Player");
	player->DontDeleteOnSceneSwap = true;
}

void Game::StartScene(const std::string& scene)
{
	this->EngineConfig.ptr_SceneHandler->LoadScene(scene, *this->EngineConfig.ptr_Camera, *this->EngineConfig.ptr_BackgroundColor);

	this->EngineConfig.ptr_Sprites->Add(this->m_PlayerController.GetPlayer());

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
	this->StartScene(sceneName);
}
