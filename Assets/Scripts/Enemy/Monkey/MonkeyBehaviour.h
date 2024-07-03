#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>

#include "Monkey.h"

class MonkeyBehaviour : public spe::IScript
{
private:
    std::vector<Monkey> m_Monkeys;
    spe::EngineConfig* m_ptr_Config;
    spe::Sprite* m_ptr_Player;

public:
    MonkeyBehaviour() = default;

	 // Can get called on start by the game/sub class
    void Start(spe::EngineConfig& cnfg);

    // Can get called 1 time per frame by the game/sub class
    void Update();

    void SpawnMonkey(const spe::Vector2& position);
};
