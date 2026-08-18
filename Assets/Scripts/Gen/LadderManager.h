#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>
#include "Scripts/Player/PlayerController.h"
#include <algorithm>
#include <unordered_set>

class LadderManager : public spe::IScript
{
private:
    std::vector<spe::Sprite*> m_LaddersOfCurrentScene;
    spe::Sprite* m_ptr_Player;
    std::string m_GoUp;

public:
    LadderManager() = default;
    spe::Sprite* IsSpriteCollided(const std::unordered_map<uint32_t, spe::Sprite*>& collidedSprites,
        std::vector<spe::Sprite*>& secondArray);

	 /* Can get called on start by the game/sub class.
		- These paramaters can get removed if you want. (remove override)
		- You may also add costum parameters. (remove override) */
    void Start(spe::EngineConfig& cnfg, const std::string& scene) override;

    // Can get called 1 time per frame by the game/sub class
    void Update();
};
