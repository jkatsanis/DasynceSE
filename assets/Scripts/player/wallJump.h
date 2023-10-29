#pragma once

#include <_header/SpriteEngine.h>

#define WALL_SLIDE_TIME 0.5f

class WallJump
{
private:
	s2d::Sprite* m_ptr_player;
	float m_wall_velocity;
	float m_wall_timer;
	bool m_on_wall;

public:
	void start(s2d::Sprite* player);

	void update(const bool& is_grounded);
};

