#pragma once

#include "Slide.h"
#include "WallJump.h"

#define PLAYER_SPEED 800
#define DOWN_ATTACK_SPEED -1000

class PlayerController : public spe::IScript
{
private:
	spe::Camera* m_ptr_Camera;
	spe::Sprite* m_ptr_Player;
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
	void Start(spe::EngineConfig& game);

	void Update() override;

	spe::Sprite* GetPlayer() { return this->m_ptr_Player; }
};
