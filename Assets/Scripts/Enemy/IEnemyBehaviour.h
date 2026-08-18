#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>


class IEnemyBehaviour
{
protected:
    spe::EngineConfig* m_ptr_Config;

    IEnemyBehaviour() = default;
public:

    virtual void Update() = 0;
    virtual void Start(spe::EngineConfig& cnfg, const std::string& scene) = 0;
    virtual void OnSceneChange() = 0;
    virtual void Spawn(const spe::Vector2& position) = 0;
};
