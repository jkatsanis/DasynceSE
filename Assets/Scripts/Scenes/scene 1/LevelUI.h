#pragma once

#include "Source/SpriteEngine.h"
#include "Scripts/Macros.h"
#include "Scripts/Enemy/IEnemy.h"
#include "Scripts/Enemy/EnemyHandler.h"
#include "Audio/Audio.h"

#include <functional>

class LevelUI : public spe::IScript
{
private:
	spe::Sprite* m_ptr_Player;
	spe::EngineConfig* m_ptr_Game;
	spe::Audio m_waterfallSound;

	static std::vector<EnemySpawn> s_FirstSceneEnemys;

public:
	LevelUI() = default;

	bool ReadingNote;

	void Update(std::function<void(const std::string&)> OnSceneChange);

	void Start(spe::EngineConfig& cnf);
};
