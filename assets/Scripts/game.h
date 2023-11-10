#pragma once

#include <_header/SpriteEngine.h>

#include <Player/playerController.h>
#include <Camera/cameraController.h>

class Game : public s2d::Base
{
private:
	PlayerController m_controller;
	CameraController m_controller_cam;
public:
	s2d::EngineConfig config;

	void start() override;
	void update() override;
};

