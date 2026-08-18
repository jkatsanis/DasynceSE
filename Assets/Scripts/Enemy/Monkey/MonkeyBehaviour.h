#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>

#include "Scripts/Player/PlayerController.h"
#include "Monkey.h"
#include "Scripts/Enemy/IEnemyBehaviour.h"

class MonkeyBehaviour : public spe::IScript, public IEnemyBehaviour
{
private:
    std::vector<Monkey> m_Monkeys;

public:
    MonkeyBehaviour() = default;

	 // Can get called on start by the game/sub class
    void Start(spe::EngineConfig& cnfg, const std::string& scene) override;

    // Can get called 1 time per frame by the game/sub class
    void Update() override;

    void Spawn(const spe::Vector2& position) override;

    void OnSceneChange() override;

    bool DamageBySprite(spe::Sprite* sprite, int damage);
};
