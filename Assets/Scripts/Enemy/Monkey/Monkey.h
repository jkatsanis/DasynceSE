#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>
#include "Scripts/General/Helthbar/Healthbar.h"

#define MONKEY_SPEED 150

class Monkey : public spe::IScript
{
private:
    spe::Sprite* m_MonkeySprite;
    Healthbar m_Healthbar;

public:
    Monkey() = default;
    
    void Start(spe::EngineConfig& config); 

    // Can get called 1 time per frame by the game/sub class
    void Update(const spe::Vector2& player_pos);

    void SetMonkeySprite(spe::Sprite* sprite) { this->m_MonkeySprite = sprite; }
};
