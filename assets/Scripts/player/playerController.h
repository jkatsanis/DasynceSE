#pragma once

#include <_header/SpriteEngine.h>

#define PLAYER_SPEED 400

class Game;
class PlayerController : public s2d::Base
{
private:
	Game* m_game;
	s2d::Sprite* m_ptr_player;
	s2d::Vector2 m_scale;
	bool m_grounded;

	void movement();

public:
	void start(Game& game);

	void update() override;
};

