#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>
#include "Scripts/General/Helthbar/Healthbar.h"
#include "Scripts/Player/PlayerController.h"

#define MONKEY_SPEED 150
#define ATTACK_COOLDOWN 0.5f

class Monkey : public spe::IScript
{
private:
    spe::Sprite* m_MonkeySprite = nullptr;
    Healthbar m_Healthbar;
    float m_AttackCooldown;
    bool m_ApplyForce;
    float m_ForceCooldown;

    void Attack();

public:
    Monkey() = default;

    void Start(spe::EngineConfig& config, spe::Sprite* sprite); 

    // Can get called 1 time per frame by the game/sub class
    void Update();
};
