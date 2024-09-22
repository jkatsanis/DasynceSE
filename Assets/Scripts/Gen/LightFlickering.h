#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>

#define FLICK_CD_MP 1000.0f

class LightFlickering : public spe::IScript
{
private:
    spe::Sprite* light;
    bool flick;
    float timer;
    bool madebig;
    float bigtimer;
    float alltimer;
    int radius;
    
    std::vector<spe::Sprite*> lights;

public:
    LightFlickering() = default;

	 // Can get called on start by the game/sub class
    void Start(spe::EngineConfig& cnfg);

    // Can get called 1 time per frame by the game/sub class
    void Update(spe::EngineConfig& cnfg);
};
