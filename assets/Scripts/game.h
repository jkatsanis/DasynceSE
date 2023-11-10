#pragma once

#include <_header/SpriteEngine.h>

#include <Player/playerController.h>
#include <Camera/cameraController.h>
#include <Enemy/enemyBehaviour.h>

class Game : public s2d::Base
{
private:
	PlayerController m_controller;
	CameraController m_controller_cam;
	EnemyBehaviour m_enemy_behaviour;
	
public:
	s2d::EngineConfig config;

	void start() override;
	void update() override;
};

