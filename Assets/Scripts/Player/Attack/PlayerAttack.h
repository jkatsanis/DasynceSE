#pragma once

#include <Source/SpriteEngine.h>
#include "AcidPotion.h"
#include <vector>

#define MAX_POTIONS 5
#define POTION_SPEED 600.0f
#define ATTACK_COOLDOWN 0.5f
#define POTION_DAMAGE 25

class PlayerAttack : public spe::IScript
{
private:
    spe::EngineConfig* m_ptr_Config;
    spe::Sprite* m_ptr_Player;
    spe::Camera* m_ptr_Camera;
    sf::RenderWindow* m_ptr_Window;

    std::vector<AcidPotion> m_Potions;
    std::vector<spe::Sprite*> m_PotionSprites;

    float m_AttackCooldown;
    float m_CurrentCooldown;

    spe::Vector2 GetMouseWorldPosition() const;
    int FindInactivePotion() const;
    void CreatePotionSprites();
    void CheckEnemyHits();

public:
    PlayerAttack();

    void Start(spe::EngineConfig& config, spe::Sprite* player, sf::RenderWindow* window);
    void Update() override;
    void OnSceneChange();
};

