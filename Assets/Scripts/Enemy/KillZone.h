#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>

class KillZone : public spe::IScript
{
public:
    KillZone() = default;

	 /* Can get called on start by the game/sub class.
		- These paramaters can get removed if you want. (remove override)
		- You may also add costum parameters. (remove override) */
    void Start(spe::EngineConfig& config);

    // Can get called 1 time per frame by the game/sub class
    void Update();

    std::vector<spe::Sprite*> m_KillZone;
    spe::Sprite* m_Player;
};
