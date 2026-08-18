#pragma once

#include "functional"
#include "Audio/Audio.h"

// Included from the editor-src
#include <Source/SpriteEngine.h>

class MachineryRoom : public spe::IScript
{
private:
    spe::Sprite* m_ptr_Player;
    spe::Sprite* m_ptr_Back;
    spe::Sprite* m_ptr_Door;
    spe::Sprite* m_ptr_DoorLevelOne;
    spe::Audio m_conveyorSound;

public:
    MachineryRoom() = default;

	 /* Can get called on start by the game/sub class.
		- These paramaters can get removed if you want. (remove override)
		- You may also add costum parameters. (remove override) */
    void Start(spe::EngineConfig& cnfg);

    // Can get called 1 time per frame by the game/sub class
    void Update(std::function<void(const std::string&)> OnSceneChange);
};
