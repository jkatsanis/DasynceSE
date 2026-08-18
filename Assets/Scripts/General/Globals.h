#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>

#include "Scripts/General/Globals.h"

class Globals : public spe::IScript
{
public:
    Globals() = default;
    
    static bool s_IsPowerEnabled;
};
