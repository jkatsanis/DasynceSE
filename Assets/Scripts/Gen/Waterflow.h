#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>

class Waterflow : public spe::IScript
{
public:
    Waterflow() = default;

	 // Can get called on start by the game/sub class
    void Start(spe::EngineConfig& cnfg);

    // Can get called 1 time per frame by the game/sub class
    void Update();
};
