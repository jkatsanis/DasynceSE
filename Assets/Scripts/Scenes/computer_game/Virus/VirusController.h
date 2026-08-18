#pragma once

#include "functional"

// Included from the editor-src
#include <Source/SpriteEngine.h>

class VirusController : public spe::IScript
{
private:
    spe::Sprite* m_ptr_Virus;
    spe::EngineConfig* m_ptr_Config;
    const spe::Sprite* m_ptr_Player;
    std::vector<spe::Sprite*> m_Lasers;

    float m_LaserTimer;
    float m_LaserTimerCap;

    float m_VirusSpeed;
    float m_teleportCounter;

    void Move();

public:
    int32_t Hearts;

    VirusController() = default;

	 /* Can get called on start by the game/sub class.
		- These paramaters can get removed if you want. (remove override)
		- You may also add costum parameters. (remove override) */
    void Start(spe::EngineConfig& cnfg);

    // Can get called 1 time per frame by the game/sub class
    void Update(std::function<void()> OnPlayerHit, std::function<void(spe::Sprite* laser, int32_t laser_speed)> OnShieldHit);

    spe::Sprite* GetVirus() { return this->m_ptr_Virus; }
};
