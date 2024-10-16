#include "PlayerController.h"
#include "Scripts/Game.h"

void PlayerController::Start(spe::EngineConfig& game)
{
	this->m_Walking = false;
	this->m_Grounded = false;
	this->ptr_Player = game.ptr_Sprites->GetByName("Player");
	this->m_Scale = this->ptr_Player->Transform.GetScale();
	this->ptr_Player->Animator.Play("idle");
	this->m_ptr_Camera = game.ptr_Camera;

	/////////////////////
	// PLAYER INITIALIZED
	/////////////////////

	this->m_LeftDefaultBoxSize = this->ptr_Player->Collider.Width.X;

	this->m_DownAttacking = true;

	this->m_Slide.start(this->ptr_Player);
	this->m_WallJump.start(this->ptr_Player);

	this->HealthBar.Start(100, game, this->ptr_Player);
	this->HealthBar.DontDeleteOnSceneSwap(game);
}

void PlayerController::Update()
{

	this->AnimationControll();
	this->LeftRight();
	this->Jump();

	if (spe::Input::OnKeyRelease(spe::KeyBoardCode::K))
	{
		this->HealthBar.Damage(5);
	}
	// this->m_slide.update(this->m_walking);
	// this->m_wall_jump.update(this->m_grounded);
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

void PlayerController::AnimationControll()
{
	// Checking when we first press the key so we play the run and stop the idle animation
	if (spe::Input::OnKeyPress(spe::KeyBoardCode::A) || spe::Input::OnKeyPress(spe::KeyBoardCode::D)
		&& !this->m_Slide.isSliding() && !this->m_Walking)
	{
		this->m_Walking = true;
		this->ptr_Player->Animator.Stop("idle");
		this->ptr_Player->Animator.Play("runv2");
	}
	else if ((spe::Input::OnKeyRelease(spe::KeyBoardCode::A) || spe::Input::OnKeyRelease(spe::KeyBoardCode::D))
		&& !spe::Input::OnKeyHold(spe::KeyBoardCode::A) && !spe::Input::OnKeyHold(spe::KeyBoardCode::D))
	{
		this->m_Walking = false;
		this->ptr_Player->Animator.Stop("runv2");
		this->ptr_Player->Animator.Play("idle");
	}
}

void PlayerController::LeftRight()
{
	if (spe::Input::OnKeyHold(spe::KeyBoardCode::A))
	{
		//if (this->m_Slide.controlWalkCondition(spe::KeyBoardCode::A))
		//{
		//	return;
		//}

		this->ptr_Player->Transform.SetScale(spe::Vector2(-this->m_Scale.X, this->m_Scale.Y));

		this->ptr_Player->Collider.Width.X = 24;
		const spe::Vector2 pos = spe::Vector2(this->ptr_Player->Transform.GetPosition().X - PLAYER_SPEED * spe::Time::s_DeltaTime,
			this->ptr_Player->Transform.GetPosition().Y);
		this->ptr_Player->Transform.SetPosition(pos);
	}
	if (spe::Input::OnKeyHold(spe::KeyBoardCode::D))
	{
		//if (this->m_Slide.controlWalkCondition(spe::KeyBoardCode::D))
		//{
		//	return;
		//}

		this->ptr_Player->Transform.SetScale(spe::Vector2(this->m_Scale.X, this->m_Scale.X));

		this->ptr_Player->Collider.Width.X = this->m_LeftDefaultBoxSize;
		const spe::Vector2 pos = spe::Vector2(this->ptr_Player->Transform.GetPosition().X + PLAYER_SPEED * spe::Time::s_DeltaTime,
			this->ptr_Player->Transform.GetPosition().Y);
		this->ptr_Player->Transform.SetPosition(pos);
	}
}

void PlayerController::Jump()
{
	this->m_Grounded = this->ptr_Player->Collider.CollidedWithTag("Floor") != nullptr;

	if (spe::Input::OnKeyPress(spe::KeyBoardCode::Space) && this->m_Grounded)
	{
		this->m_Grounded = false;
		this->ptr_Player->Physicsbody.Velocity.Y = 0;
		spe::Physics::AddForce(this->ptr_Player, spe::Vector2(0, 1), 600);
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

PlayerController* PlayerController::instance = nullptr;