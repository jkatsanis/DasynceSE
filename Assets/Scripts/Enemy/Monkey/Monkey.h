#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>
#include "Scripts/General/Helthbar/Healthbar.h"

#define MONKEY_SPEED 150

class Monkey : public spe::IScript
{
private:
    spe::Sprite* m_MonkeySprite = nullptr;
    Healthbar m_Healthbar;

    void Attack(spe::Sprite* player);

public:
    void Start(spe::EngineConfig& config, spe::Sprite* sprite); 

    // Can get called 1 time per frame by the game/sub class
    void Update(spe::Sprite* player);
};
