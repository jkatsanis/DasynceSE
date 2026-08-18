#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>
#include "Scripts/Enemy/IEnemyBehaviour.h"
#include "Scripts/Enemy/Rat/Rat.h"

class RatBehaviour : public spe::IScript, public IEnemyBehaviour
{
private:
    std::vector<Rat> m_Rats;

public:
    RatBehaviour() = default;

    void Start(spe::EngineConfig& cnfg, const std::string& scene) override;
    void Update();
    void OnSceneChange();
    void Spawn(const spe::Vector2& position) override;
    bool DamageBySprite(spe::Sprite* sprite, int damage);
};
