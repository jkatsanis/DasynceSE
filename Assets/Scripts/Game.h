#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>

#include "Player/PlayerController.h"
#include "Scenes/scene 1/LevelUI.h"
#include "Camera/PlayerCamera.h"
#include "Scenes/computer_room/ComputerRoom.h"
#include "Scripts/Enemy/EnemyHandler.h"

class Game : public spe::IScript
{		
private:
	PlayerController* m_ptr_PlayerController;
	LevelUI m_LevelUI;
	PlayerCamera m_Camera;
	ComputerRoom m_ComputerRoom;
	EnemyHandler m_EnemyHandler;

	spe::Sprite* m_Player;

public:
	spe::EngineConfig EngineConfig;
	
	// Gets called on start of the engine
	void Start() override;

	void StartScene(const std::string& scene);

	// Gets called once per frame
	void Update() override;

	// Should get called on stop
	void OnStop();

	void OnSceneChange(const std::string& sceneName);
};

