#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>
#include "Scripts/General/Helthbar/PlayerHealthbar.h"
#include "Scripts/Player/PlayerController.h"
#include "Scripts/Enemy/IEnemy.h"

#define RAT_SPEED 150
#define RAT_2_ATTACK_COOLDOWN 0.1f

class Rat : public spe::IScript, public IEnemy
{
private:
    void Attack() override;
    bool m_InRange;
    float m_AttackCooldown;

public:
    Rat() = default;

    void Start(spe::EngineConfig& config, spe::Sprite* sprite) override;

    void Update() override;

    void TakeDamage(int damage) override;
};
