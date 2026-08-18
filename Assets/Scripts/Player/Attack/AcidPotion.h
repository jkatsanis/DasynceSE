#pragma once

#include <Source/SpriteEngine.h>

class AcidPotion;

class AcidPotion
{
private:
    enum class LandedState
    {
        None,
        Lingering,
        FadingOut
    };

    spe::Sprite* m_Sprite;
    spe::Vector2 m_Velocity;
    float m_Gravity;
    float m_LifeTime;
    float m_MaxLifeTime;
    bool m_Active;
    bool m_HasDealtDamage;
    LandedState m_LandedState;
    float m_LandedTimer;
    int m_Damage;

public:
    AcidPotion();

    void Init(spe::Sprite* sprite);
    void Launch(const spe::Vector2& startPos, const spe::Vector2& targetPos, float speed);
    void Update();
    bool IsActive() const { return m_Active; }
    bool IsLanded() const { return m_LandedState != LandedState::None; }
    bool HasDealtDamage() const { return m_HasDealtDamage; }
    void MarkDamageDealt() { m_HasDealtDamage = true; }
    void Deactivate();
    void OnLand();

    spe::Sprite* GetSprite() const { return m_Sprite; }
    int GetDamage() const { return m_Damage; }
};

