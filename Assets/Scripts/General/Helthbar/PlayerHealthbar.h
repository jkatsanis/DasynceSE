#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>

class PlayerHealthbar : public spe::IScript
{
private:
	static int s_m_TotalHealthBars;

	spe::Sprite* m_HealthBar = nullptr;
	spe::Sprite* m_HealthRect = nullptr; // The foregound rect aka the real health

	int m_Health;
	int m_TotalHealth;

public:
	PlayerHealthbar() = default;

	void DontDeleteOnSceneSwap(spe::EngineConfig& cnfg);

    // Can get called on start by the game/sub class
	void Start(int health, spe::EngineConfig& cnfg, spe::Sprite* to);

    void Damage(int health);
	[[nodiscard]] int GetHealth() const { return  this->m_Health; }
	bool HasDied() const { return this->GetHealth() <= 0;}
};
