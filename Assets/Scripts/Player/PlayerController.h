#pragma once

#include "Slide.h"
#include "WallJump.h"
#include "Scripts/General/Helthbar/Healthbar.h"

#define PLAYER_SPEED 800
#define DOWN_ATTACK_SPEED -1000

class PlayerController : public spe::IScript
{
private:
	static PlayerController* instance;

private:
	spe::Camera* m_ptr_Camera;
	spe::Vector2 m_Scale;
	bool m_Grounded;
	bool m_Walking;
	float m_LeftDefaultBoxSize;

	Slide m_Slide;
	WallJump m_WallJump;

	bool m_DownAttacking;

	void AnimationControll();
	void LeftRight();
	void Jump();
	void DownAttack();


public:
	PlayerController() = default;

	spe::Sprite* ptr_Player;
	Healthbar HealthBar;

	void Start(spe::EngineConfig& game);

	void Update() override;

	static void Shutdown();

	static PlayerController& GetInstance();
};
