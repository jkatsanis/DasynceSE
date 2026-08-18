#include "PlayerController.h"
#include "Scripts/Game.h"
#include "Audio/Audio.h"

void PlayerController::Start(spe::EngineConfig& game, sf::RenderWindow* window)
{
	this->m_Grounded = false;
	this->ptr_Player = game.ptr_Sprites->GetByName("Player");
	this->m_Scale = this->ptr_Player->Transform.GetScale();
	this->m_ptr_Camera = game.ptr_Camera;
	this->m_LandingSound = this->ptr_Player->Audio.GetAudioByName("DropFloor");
	this->m_LandingSoundWater = this->ptr_Player->Audio.GetAudioByName("DropWater");
	this->m_LandingSound->Load();
	this->m_LandingSoundWater->Load();
	this->m_playSound = true;
	/////////////////////
	// PLAYER INITIALIZED
	/////////////////////

	this->m_LeftDefaultBoxSize = this->ptr_Player->Collider.Width.X;

	this->m_DownAttacking = true;

	this->m_Slide.start(this->ptr_Player);
	this->m_WallJump.start(this->ptr_Player);

	this->HealthBar.Start(100, game, this->ptr_Player);
	this->HealthBar.DontDeleteOnSceneSwap(game);

	this->LadderController.Start(this->ptr_Player);

	this->m_Slide.start(this->ptr_Player);

	// Initialize attack system
	this->m_Attack.Start(game, this->ptr_Player, window);
}

void PlayerController::Update()
{
	// stop landing particles after a short duration
	if (this->m_ParticlesPlaying) {
		this->m_ParticleStopTimer -= spe::Time::s_DeltaTime;
		if (this->m_ParticleStopTimer <= 0.0f) {
			this->ptr_Player->Particles.Stop();
			this->m_ParticlesPlaying = false;
		}
	}

	bool leave = false;
	this->Jump();
	this->LadderController.Update();

	if (!this->LadderController.IsOnLadder)
	{
		this->AnimationControl();
		this->LeftRight();

		if (spe::Input::OnKeyRelease(spe::KeyBoardCode::K))
		{
			this->HealthBar.Damage(5);
		}
		this->m_Slide.update(this->m_IsWalking);
		// this->m_wall_jump.update(this->m_grounded);
	}

	this->m_Attack.Update();
}

void PlayerController::AnimationControl()
{
	// Checking when we first press the key so we play the run and stop the idle animation


	if (this->m_Slide.isSliding())
	{
		return;
	}

	bool runInput = spe::Input::OnKeyHold(spe::KeyBoardCode::A) || spe::Input::OnKeyHold(spe::KeyBoardCode::D);

	if (runInput && this->ptr_Player->Animator.GetAnimationPlaying().Name != "runv2")
	{
		this->ptr_Player->Animator.Play("runv2");
		this->m_IsWalking = true;
	}
	else if (!runInput && this->ptr_Player->Animator.GetAnimationPlaying().Name != "idle")
	{
		this->m_IsWalking = false;
		this->ptr_Player->Animator.Play("idle");

	}
}

void PlayerController::LeftRight()
{
	if (spe::Input::OnKeyHold(spe::KeyBoardCode::A))
	{
		if (this->m_Slide.controlWalkCondition(spe::KeyBoardCode::A))
		{
			return;
		}

		this->ptr_Player->Transform.SetScale(spe::Vector2(-this->m_Scale.X, this->m_Scale.Y));

		this->ptr_Player->Collider.Width.X = 24;
		const spe::Vector2 pos = spe::Vector2(this->ptr_Player->Transform.GetPosition().X - PLAYER_SPEED * spe::Time::s_DeltaTime,
		                                      this->ptr_Player->Transform.GetPosition().Y);
		this->ptr_Player->Transform.SetPosition(pos);
		OnMovementEvent();
	}
	if (spe::Input::OnKeyHold(spe::KeyBoardCode::D))
	{
		if (this->m_Slide.controlWalkCondition(spe::KeyBoardCode::D))
		{
			return;
		}

		this->ptr_Player->Transform.SetScale(spe::Vector2(this->m_Scale.X, this->m_Scale.X));

		this->ptr_Player->Collider.Width.X = this->m_LeftDefaultBoxSize;
		const spe::Vector2 pos = spe::Vector2(this->ptr_Player->Transform.GetPosition().X + PLAYER_SPEED * spe::Time::s_DeltaTime,
		                                      this->ptr_Player->Transform.GetPosition().Y);
		this->ptr_Player->Transform.SetPosition(pos);
		OnMovementEvent();
	}
}


void PlayerController::Jump()
{
	const spe::Sprite* collider = this->ptr_Player->Collider.CollidedWithTag("Floor");
	const bool wasGrounded = this->m_Grounded;
	this->m_Grounded = (collider != nullptr) || this->LadderController.IsOnLadder;

	if (wasGrounded == false && this->m_Grounded) {
		if (this->ptr_Player->Collider.CollidedWithTag("water") == nullptr) {
			this->m_LandingSound->Play();
			// Make particles brown/grey for regular floor
			this->ptr_Player->Particles.GetConfig().StartColorMin = sf::Color(139, 119, 101, 255);
			this->ptr_Player->Particles.GetConfig().StartColorMax = sf::Color(160, 140, 120, 255);
			this->ptr_Player->Particles.GetConfig().EndColorMin = sf::Color(139, 119, 101, 0);
			this->ptr_Player->Particles.GetConfig().EndColorMax = sf::Color(160, 140, 120, 0);
			this->ptr_Player->Particles.Play();
		}
		else {
			this->m_LandingSoundWater->Play();
			// Make particles blue for water
			this->ptr_Player->Particles.GetConfig().StartColorMin = sf::Color(64, 164, 223, 255);
			this->ptr_Player->Particles.GetConfig().StartColorMax = sf::Color(100, 180, 240, 255);
			this->ptr_Player->Particles.GetConfig().EndColorMin = sf::Color(64, 164, 223, 0);
			this->ptr_Player->Particles.GetConfig().EndColorMax = sf::Color(100, 180, 240, 0);
			this->ptr_Player->Particles.Play();
		}
		this->m_ParticlesPlaying = true;
		this->m_ParticleStopTimer = PARTICLE_DURATION;
	}
	// while jumping
	else if (!this->m_Grounded) {
		OnMovementEvent();
	}

	if (collider == nullptr)
	{
		return;
	}

	if (spe::Input::OnKeyPress(spe::KeyBoardCode::Space) && this->m_Grounded)
	{
		this->m_FloorJumpedOff = collider->GetId();
		this->ptr_Player->Physicsbody.Velocity.Y = 0;
		spe::Physics::AddForce(this->ptr_Player, spe::Vector2(0, 1), 700);
	}
}

void PlayerController::DownAttack()
{
	if (spe::Input::OnKeyPress(spe::KeyBoardCode::S))
	{
		this->m_DownAttacking = true;
		this->ptr_Player->Physicsbody.Velocity.Y = DOWN_ATTACK_SPEED;
	}
	if (this->m_Grounded)
	{
		this->m_DownAttacking = false;
	}
}

void PlayerController::OnMovementEvent() const
{ // call when there is movement e.g. running or jumping
	const spe::Vector2 pos = this->ptr_Player->Transform.GetPosition();
	spe::Audio::SetListenerPosition(pos.X, pos.Y);

}
void PlayerController::ResetAnimation()
{
	this->ptr_Player->Animator.Play("runv2");
	this->m_IsWalking = true;
}

void PlayerController::OnSceneChange()
{
	this->m_Attack.OnSceneChange();
}

void PlayerController::Shutdown()
{
	delete PlayerController::instance;
}

PlayerController& PlayerController::GetInstance()
{
	if (PlayerController::instance == nullptr)
	{
		PlayerController::instance = new PlayerController();
	}
	return *instance;
}


PlayerController* PlayerController::instance = nullptr;