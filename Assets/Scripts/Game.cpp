#include "Game.h"

void Game::Start()
{
	this->StartScene("computer_room");
}

void Game::StartScene(const std::string& scene)
{
	this->EngineConfig.ptr_SceneHandler->LoadScene(scene, *this->EngineConfig.ptr_Camera, *this->EngineConfig.ptr_BackgroundColor);
	if (this->EngineConfig.ptr_SceneHandler->CurrentScene == "scene 1")
	{
		this->m_LevelUI.Start(this->EngineConfig);
		spe::Sprite* woa = this->EngineConfig.ptr_Sprites->GetByName("Water_1");
		woa->Animator.Play("WaterFlow");
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
		this->m_ComputerRoom.Update();
	}
}

void Game::OnSceneChange(const std::string& sceneName)
{
	spe::Camera& camera = *this->EngineConfig.ptr_Camera;
	this->EngineConfig.ptr_SceneHandler->LoadScene(sceneName, camera, *this->EngineConfig.ptr_BackgroundColor);

	this->StartScene(sceneName);
}
