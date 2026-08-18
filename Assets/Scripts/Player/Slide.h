#pragma once

#include "Source/SpriteEngine.h"

#define SLIDE_FORCE 1200.0f

enum class DashKey
{
	None = 0,
	A,
	D
};
class Slide : public spe::IScript
{
private:
	spe::Sprite* m_ptr_player;
	DashKey m_dash_key;
	spe::Audio* m_ptr_dash_sound;

	float m_slide_time;
	float m_time_slided;
	bool m_sliding;

	void animationControl(const bool& is_walking);
	bool slideCondition(const bool& is_walking);

public:
	Slide() = default;

	void start(spe::Sprite* player);

	void update(const bool& is_walking);

	void stop();

	bool isSliding() const { return this->m_sliding; }

	bool controlWalkCondition(spe::KeyBoardCode directio);
};
