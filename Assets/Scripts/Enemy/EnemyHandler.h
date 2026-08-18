#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>

#include "Monkey/MonkeyBehaviour.h"
#include "IEnemyBehaviour.h"
#include "Rat/RatBehaviour.h"

class EnemyHandler : public spe::IScript
{
private:
    static EnemyHandler m_Instance;

public:
    MonkeyBehaviour MonkeyBehaviourObject;
    RatBehaviour RatBehaviourObject;

    EnemyHandler() = default;

    static EnemyHandler& GetInstance() { return EnemyHandler::m_Instance; }

	 // Can get called on start by the game/sub class
    void Start(spe::EngineConfig& cnfg, const std::string& scene);

    // Can get called 1 time per frame by the game/sub class
    void Update();

    void OnSceneChange();

    // Damage an enemy by its sprite pointer
    bool DamageEnemyBySprite(spe::Sprite* sprite, int damage);
};
