#pragma once

#include "Source/SpriteEngine.h"

class LevelUI : public spe::IScript
{
private:
	spe::Sprite* m_ptr_Player;

public:
	bool ReadingNote;

	void Update() override;

	void Start(spe::EngineConfig& cnf);
};
