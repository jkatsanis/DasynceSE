#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>
#include "Scripts/General/Helthbar/PlayerHealthbar.h"

enum class EnemyType
{
    Monkey = 0,
    Rat = 1
};


struct EnemySpawn
{
    spe::Vector2 Position;
    EnemyType Type;
};


class IEnemy 
{
protected:
    PlayerHealthbar m_Healthbar;
    spe::Sprite* m_EnemySprite = nullptr;

    virtual void Attack() = 0;

    IEnemy() = default;

public:

    virtual void Start(spe::EngineConfig& config, spe::Sprite* sprite) = 0;

    virtual void Update() = 0;

    virtual void TakeDamage(int damage) = 0;
    [[nodiscard]] spe::Sprite* GetSprite() const { return m_EnemySprite; }
    [[nodiscard]] bool HasDied() const { return m_Healthbar.HasDied(); }
};
