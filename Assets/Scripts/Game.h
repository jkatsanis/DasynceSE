#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>

#include "Player/PlayerController.h"
#include "Scenes/scene 1/LevelUI.h"
#include "Camera/PlayerCamera.h"
#include "Scenes/computer_room/ComputerRoom.h"

class Game : public spe::IScript
{		
private:
	PlayerController m_PlayerController;
	LevelUI m_LevelUI;
	PlayerCamera m_Camera;
	ComputerRoom m_ComputerRoom;

public:
	spe::EngineConfig EngineConfig;
	
	// Gets called on start of the engine
	void Start() override;

	void StartScene(const std::string& scene);

	// Gets called once per frame
	void Update() override;

	void OnSceneChange(const std::string& sceneName);
};

