#pragma once

#include <_header/SpriteEngine.h>
#include "slide.h"
#include "wallJump.h"

#define PLAYER_SPEED 800
#define DOWN_ATTACK_SPEED -1000

class Game;
class PlayerController : public s2d::Base
{
private:
	s2d::Sprite* m_ptr_player;
    s2d::Vector2 m_scale;
	bool m_grounded;
	bool m_walking;
	float m_left_default_box_size;

	Slide m_slide;
	WallJump m_wall_jump;

	bool m_down_attacking;

	void animationControll();
	void leftRight();
	void jump();
	void downAttack();


public:
	void start(Game& game);

	void update() override;
};

