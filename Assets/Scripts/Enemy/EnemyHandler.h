#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>

#include "Monkey/MonkeyBehaviour.h"

class EnemyHandler : public spe::IScript
{
private:
    MonkeyBehaviour m_MonkeyBehaviour;

public:
    EnemyHandler() = default;

	 // Can get called on start by the game/sub class
    void Start(spe::EngineConfig& cnfg);

    // Can get called 1 time per frame by the game/sub class
    void Update();

    void OnSceneChange();
};
