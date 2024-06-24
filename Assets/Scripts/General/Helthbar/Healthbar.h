#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>

class Healthbar : public spe::IScript
{
private:
	spe::Sprite* m_HealthBar;
	spe::Sprite* m_HealthRect; // The foregound rect aka the real health

	int m_Health;
	int m_TotalHealth;

public:
    // Can get called on start by the game/sub class
	void Start(int health, spe::EngineConfig& cnfg);

    void Damage(int health);
};
