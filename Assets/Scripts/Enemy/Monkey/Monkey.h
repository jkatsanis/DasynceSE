#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>
#include "Scripts/General/Helthbar/PlayerHealthbar.h"
#include "Scripts/Player/PlayerController.h"
#include "Scripts/Enemy/IEnemy.h"

#define MONKEY_SPEED 150
#define MONKEY_ATTACK_COOLDOWN 0.5f

class Monkey : public spe::IScript, public IEnemy
{
private:
    float m_AttackCooldown = 0.0f;
    bool m_ApplyForce = false;
    float m_ForceCooldown = 0.0f;
    bool m_InRange = false;

    void Attack() override;

public:
    Monkey() = default;

    void Start(spe::EngineConfig& config, spe::Sprite* sprite) override;

    void Update() override;

    void TakeDamage(int damage) override;
};
