#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>

#include "Player/PlayerController.h"
#include "Scenes/scene 1/LevelUI.h"
#include "Camera/PlayerCamera.h"
#include "Enemy/KillZone.h"
#include "Scenes/computer_room/ComputerRoom.h"
#include "Scripts/Enemy/EnemyHandler.h"
#include "Scripts/Gen/LightFlickering.h"
#include "Scripts/Gen/Waterflow.h"
#include "Scripts/Gen/LadderManager.h"
#include "Scripts/Scenes/computer_game/ComputerGame.h"
#include "Scripts/Scenes/machinery_room/MachineryRoom.h"
#include "Audio/Audio.h"

class Game : public spe::IScript
{		
private:
	PlayerController* m_ptr_PlayerController;
	LevelUI m_LevelUI;
	PlayerCamera m_Camera;
	ComputerRoom m_ComputerRoom;
	EnemyHandler* m_ptr_EnemyHandler;
	LightFlickering m_LightFlickering;
	Waterflow m_WaterFlow;
	ComputerGame m_ComputerGame;
	MachineryRoom m_MachineryRoom;
	LadderManager m_LadderManager;
	spe::Audio m_backgroundMusic;
	KillZone m_KillZone;


	spe::Sprite* m_Player;

	int32_t m_StartCnt = 0;

public:
	spe::EngineConfig EngineConfig;
	
	Game() = default;

	// Gets called on start of the engine
	void Start(const std::string& scene);

	// Gets called once per frame
	void Update() override;

	bool LeaveConditions();

	// Should get called on stop
	void OnStop();

	void OnSceneChange(const std::string& sceneName);

	void PlayBackgroundMusic(const std::string& path);
};

