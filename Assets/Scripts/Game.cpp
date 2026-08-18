#include "Game.h"

#define DEFAULT_BG_MUSIC_PATH "Assets/Audio/Music/MysteriousBackgroundMusicSeamless.wav"

void Game::Start(const std::string& scene)
{
	std::string to_load = scene;


	if (m_StartCnt == 0)
	{
		//o_load = "ExperimentScene";
		to_load = "scene 1";
	}

	this->EngineConfig.LoadScene(to_load);

	if (this->m_StartCnt == 0)
	{
		this->m_Player = spe::PrefabRepository::GetPrefabByName("Player");
		this->EngineConfig.ptr_Sprites->Add(this->m_Player);
		this->EngineConfig.DontDeleteOnSceneSwap(this->m_Player);
		this->m_ptr_PlayerController = &PlayerController::GetInstance();
		this->m_ptr_PlayerController->Start(this->EngineConfig, this->EngineConfig.ptr_Window);

		this->m_ptr_EnemyHandler = &EnemyHandler::GetInstance();
	}
	this->m_StartCnt++;

	if (to_load == "scene 1")
	{
		this->m_ptr_EnemyHandler->Start(this->EngineConfig, to_load);
		this->m_WaterFlow.Start(this->EngineConfig, to_load);
		this->m_LevelUI.Start(this->EngineConfig);
		this->m_Player->Transform.SetPosition(spe::Vector2(47.3539f, -125.381f));
		this->PlayBackgroundMusic(DEFAULT_BG_MUSIC_PATH);
	}

	if (to_load == "computer_room")
	{
		this->m_ComputerRoom.Start(this->EngineConfig);
		this->PlayBackgroundMusic(DEFAULT_BG_MUSIC_PATH);
	}

	if (to_load == "MachineryRoom")
	{
		this->m_MachineryRoom.Start(this->EngineConfig);
		this->PlayBackgroundMusic(DEFAULT_BG_MUSIC_PATH); // TODO: possibly change for better fits, though its probably better to stay consistent with the music
	}

	this->m_Camera.Start(this->EngineConfig.ptr_Camera, this->m_Player);

	if (to_load == "compiuter_game")
	{
		this->m_ComputerGame.Start(this->EngineConfig);
		// this->PlayBackgroundMusic("Assets/Audio/Music/8BitGameMusic.wav"); // TODO: search fitting music
		this->PlayBackgroundMusic("Assets/Audio/Music/A-Polite-Thanks--by--Tueftler.wav"); // TODO: REMOVE!!! just a placeholder for testing the music transition
	}

	this->m_LightFlickering.Start(this->EngineConfig);
	this->m_LadderManager.Start(this->EngineConfig, scene);
	this->m_KillZone.Start(this->EngineConfig);
}

void Game::OnStop()
{
	PlayerController::Shutdown();
}

void Game::Update()
{	
	std::string fps = "FPS: " + std::to_string(spe::Time::s_FPS);
	ImGui::Text(fps.c_str());

	if (this->EngineConfig.ptr_SceneHandler->CurrentScene == "compiuter_game")
	{
		this->m_ComputerGame.Update([this](const std::string& sceneName) {
			this->OnSceneChange(sceneName);
		});

		return;
	}

	if (this->m_ptr_PlayerController->HealthBar.HasDied())
	{
		ImGui::Text("You're dead.");
		this->OnSceneChange("DeathScene");
		return;
	}

	if (true)
	{
		// Movement
		this->m_ptr_PlayerController->Update();
	}

	// Cmaera
	this->m_Camera.Update();

	// Enemy update
	this->m_ptr_EnemyHandler->Update();

	// Light animations
	this->m_LightFlickering.Update();

	this->m_LadderManager.Update();

	this->m_KillZone.Update();


	if (this->EngineConfig.ptr_SceneHandler->CurrentScene == "scene 1")
	{
		// UI
		this->m_LevelUI.Update([this](const std::string& sceneName) {
			this->OnSceneChange(sceneName);
		});
	}
	else if (this->EngineConfig.ptr_SceneHandler->CurrentScene == "computer_room")
	{
		this->m_ComputerRoom.Update([this](const std::string& sceneName) {
			this->OnSceneChange(sceneName);
		});
	}
	else if (this->EngineConfig.ptr_SceneHandler->CurrentScene == "MachineryRoom")
	{
		this->m_MachineryRoom.Update([this](const std::string& sceneName) {
			this->OnSceneChange(sceneName);
	});
	}
}

bool Game::LeaveConditions()
{
	bool leave = false;

	// Machinery

	return leave;

}

void Game::OnSceneChange(const std::string& sceneName)
{
	this->m_ptr_EnemyHandler->OnSceneChange();
	this->m_ptr_PlayerController->OnSceneChange();

	this->EngineConfig.LoadScene(sceneName);


	if (sceneName == "computer_room")
	{
		this->m_ptr_PlayerController->ptr_Player->Transform.Teleport(COMPUTER_ROOM_TP_POSITION);
	}
	else if (sceneName == "scene 1")
	{
		this->m_ptr_PlayerController->ptr_Player->Transform.Teleport(KANAL_TP_POSITION);
	}

	this->m_ptr_PlayerController->ResetAnimation();
}

void Game::PlayBackgroundMusic(const std::string& path)
{
	if (m_backgroundMusic.GetPath() == path) {
		return; // no need to play the same music again
	}
	m_backgroundMusic.Stop(); // stop previous music if any
	m_backgroundMusic.Configure(path, spe::Audio::AudioType::MUSIC, "bgmusic");
	m_backgroundMusic.SetVolume(50);
	m_backgroundMusic.SetLoop(true);
	m_backgroundMusic.Load();
	m_backgroundMusic.Play();
}