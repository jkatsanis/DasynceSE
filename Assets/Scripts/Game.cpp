#include "Game.h"

void Game::Start()
{
	const std::string scene_name = "scene 1";

	this->m_Player = spe::PrefabRepository::GetPrefabByName("Player");

	this->EngineConfig.ptr_Sprites->Add(this->m_Player);

	this->EngineConfig.DontDeleteOnSceneSwap(this->m_Player);

	this->m_ptr_PlayerController = &PlayerController::GetInstance();
	this->m_ptr_PlayerController->Start(this->EngineConfig);

	this->StartScene(scene_name);

	this->m_EnemyHandler.Start(this->EngineConfig);

	this->m_LightFlickering.Start(this->EngineConfig);

	this->m_WaterFlow.Start(this->EngineConfig);
}

void Game::OnStop()
{
	PlayerController::Shutdown();
}


void Game::StartScene(const std::string& scene)
{
	this->EngineConfig.LoadScene(scene);

	this->m_Camera.Start(this->EngineConfig.ptr_Camera, this->m_Player);

	if (this->EngineConfig.ptr_SceneHandler->CurrentScene == "scene 1")
	{
		this->m_LevelUI.Start(this->EngineConfig);
		this->EngineConfig.ptr_Camera->SetZoom(0.75f);
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
	this->m_ptr_PlayerController->Update();

	// Cmaera
	this->m_Camera.Update();

	// Enemy update
	this->m_EnemyHandler.Update();	

	// Light animations
	this->m_LightFlickering.Update(EngineConfig);


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
	this->m_EnemyHandler.OnSceneChange();

	if (sceneName == "computer_room")
	{
		this->m_ptr_PlayerController->ptr_Player->Transform.Teleport(COMPUTER_ROOM_TP_POSITION);
	}
	else if (sceneName == "scene 1")
	{
		this->m_ptr_PlayerController->ptr_Player->Transform.Teleport(KANAL_TP_POSITION);
	}
	this->StartScene(sceneName);
}
