#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>

#include "Scripts/Macros.h"

#include "functional"

class ComputerRoom : public spe::IScript
{
private:
	spe::Sprite* m_ptr_Player;
public:
   // Can get called on start by the game/sub class
   void Start(spe::EngineConfig& config);

   // Can get called 1 time per frame by the game/sub class
   void Update(std::function<void(const std::string&)> OnSceneChange);
};
