#pragma once

#include "Source/SpriteEngine.h"
#include "Scripts/Macros.h"

#include <functional>

class LevelUI : public spe::IScript
{
private:
	spe::Sprite* m_ptr_Player;
	spe::EngineConfig* m_ptr_Game;

public:
	LevelUI() = default;

	bool ReadingNote;

	void Update(std::function<void(const std::string&)> OnSceneChange);

	void Start(spe::EngineConfig& cnf);
};
