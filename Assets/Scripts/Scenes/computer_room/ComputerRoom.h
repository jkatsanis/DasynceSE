#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>

class ComputerRoom : public spe::IScript
{
public:
   // Can get called on start by the game/sub class
   void Start();

   // Can get called 1 time per frame by the game/sub class
   void Update();
};
