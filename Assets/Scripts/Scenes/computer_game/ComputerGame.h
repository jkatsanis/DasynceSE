#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>
#include "functional"
#include "Virus/VirusController.h"

class ComputerGame : public spe::IScript
{
private:
    spe::Sprite* ptr_PlayerPx;
    spe::Sprite* ptr_Shield;
    VirusController m_VController;

    int32_t m_Health;

    void DisplayHealth();
    void OnPlayerHit();
    void OnShieldHit(spe::Sprite* laser, int32_t laser_speed);
    void PlayerMovement();
    void ShieldMovement();

public:
    ComputerGame() = default;

	 /* Can get called on start by the game/sub class.
		- These paramaters can get removed if you want. (remove override)
		- You may also add costum parameters. (remove override) */
    void Start(spe::EngineConfig& cnfg);

    // Can get called 1 time per frame by the game/sub class
    void Update(std::function<void(const std::string&)> OnSceneChange);

};
