#pragma once

#include "Slide.h"
#include "WallJump.h"
#include "Scripts/General/Helthbar/PlayerHealthbar.h"
#include "PlayerLadderController.h"
#include "Audio/Audio.h"
#include "Attack/PlayerAttack.h"

#define PLAYER_SPEED 800
#define DOWN_ATTACK_SPEED -1000
#define PARTICLE_DURATION 0.3f

class PlayerController final : public spe::IScript
{
private:
	static PlayerController* instance;

private:
	spe::Camera* m_ptr_Camera;
	spe::Vector2 m_Scale;
	bool m_Grounded;
	float m_LeftDefaultBoxSize;
	uint32_t m_FloorJumpedOff;
	spe::Audio* m_LandingSound;
	spe::Audio* m_LandingSoundWater;
	bool m_playSound;
	float m_ParticleStopTimer = 0.0f;
	bool m_ParticlesPlaying = false;

	bool m_IsWalking;

	Slide m_Slide;
	WallJump m_WallJump;

	bool m_DownAttacking;

	PlayerAttack m_Attack;

	void AnimationControl();
	void LeftRight();
	void Jump();
	void DownAttack();
	void OnMovementEvent() const;


public:
	PlayerController() = default;

	spe::Sprite* ptr_Player;
	PlayerHealthbar HealthBar;
	PlayerLadderController LadderController;

	void Start(spe::EngineConfig& game, sf::RenderWindow* window);

	void Update() override;
	void ResetAnimation();
	void OnSceneChange();


	static void Shutdown();

	static PlayerController& GetInstance();
};
