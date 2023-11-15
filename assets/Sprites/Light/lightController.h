#pragma once

#include <_header/SpriteEngine.h>

class LightController : s2d::Base
{
private:
	s2d::Sprite* m_lamp_light;

public:
	void update() override;
	void start(s2d::EngineConfig& config);
};

