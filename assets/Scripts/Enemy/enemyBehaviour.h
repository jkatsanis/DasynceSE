#pragma once

#include <_header/SpriteEngine.h>

class EnemyBehaviour : s2d::Base
{
private:
	s2d::Sprite* m_ptr_enemy;
public:

	void update() override;
	void start(s2d::EngineConfig& config);
};

