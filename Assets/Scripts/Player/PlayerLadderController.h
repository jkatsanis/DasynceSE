#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>
#include "Audio/Audio.h"

#define LADDER_GAP 20
#define LADDER_TIMER 0.17

class PlayerLadderController : public spe::IScript
{
private:
    spe::Sprite* m_ptr_Player;
    float m_Timer;

public:
    spe::Sprite* m_ptr_Ladder;
    bool IsOnLadder;

    PlayerLadderController() = default;

	 /* Can get called on start by the game/sub class.
		- These paramaters can get removed if you want. (remove override)
		- You may also add costum parameters. (remove override) */
    void Start(spe::Sprite* player);

    void StartClimb(spe::Sprite* ladder);

    // Can get called 1 time per frame by the game/sub class
    void Update();
};
