#include "PlayerController.h"
#include "Scripts/Game.h"

void PlayerController::Start(spe::EngineConfig& game)
{
	this->m_Walking = false;
	this->m_Grounded = false;
	this->m_ptr_Player = game.ptr_Sprites->GetByName("Player");
	this->m_Scale = this->m_ptr_Player->Transform.GetScale();
	this->m_ptr_Player->Animator.Play("idle");

	this->m_ptr_Camera = game.ptr_Camera;
	/////////////////////
	// PLAYER INITIALIZED
	/////////////////////

	this->m_LeftDefaultBoxSize = this->m_ptr_Player->Collider.Width.X;

	this->m_DownAttacking = true;

	this->m_Slide.start(this->m_ptr_Player);
	this->m_WallJump.start(this->m_ptr_Player);

	this->m_ptr_Camera->SetZoom(0.7f);
}

void PlayerController::Update()
{
	this->AnimationControll();
	this->LeftRight();
	this->Jump();

	// this->m_slide.update(this->m_walking);
	// this->m_wall_jump.update(this->m_grounded);
	

	spe::Vector2 pos = spe::Vector2(this->m_ptr_Player->Transform.GetPosition().X, this->m_ptr_Player->Transform.GetPosition().Y + 170);
	pos.Y *= -1;
	this->m_ptr_Camera->Position = pos;
}

void PlayerController::AnimationControll()
{
	// Checking when we first press the key so we play the run and stop the idle animation
	if (spe::Input::OnKeyPress(spe::KeyBoardCode::A) || spe::Input::OnKeyPress(spe::KeyBoardCode::D)
		&& !this->m_Slide.isSliding() && !this->m_Walking)
	{
		this->m_Walking = true;
		this->m_ptr_Player->Animator.Stop("idle");
		this->m_ptr_Player->Animator.Play("runv2");
	}
	else if ((spe::Input::OnKeyRelease(spe::KeyBoardCode::A) || spe::Input::OnKeyRelease(spe::KeyBoardCode::D))
		&& !spe::Input::OnKeyHold(spe::KeyBoardCode::A) && !spe::Input::OnKeyHold(spe::KeyBoardCode::D))
	{
		this->m_Walking = false;
		this->m_ptr_Player->Animator.Stop("runv2");
		this->m_ptr_Player->Animator.Play("idle");
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

		this->m_ptr_Player->Transform.SetScale(spe::Vector2(-this->m_Scale.X, this->m_Scale.Y));

		this->m_ptr_Player->Collider.Width.X = 24;
		const spe::Vector2 pos = spe::Vector2(this->m_ptr_Player->Transform.GetPosition().X - PLAYER_SPEED * spe::Time::s_DeltaTime,
			this->m_ptr_Player->Transform.GetPosition().Y);
		this->m_ptr_Player->Transform.SetPosition(pos);
	}
	if (spe::Input::OnKeyHold(spe::KeyBoardCode::D))
	{
		if (this->m_Slide.controlWalkCondition(spe::KeyBoardCode::D))
		{
			return;
		}

		this->m_ptr_Player->Transform.SetScale(spe::Vector2(this->m_Scale.X, this->m_Scale.X));

		this->m_ptr_Player->Collider.Width.X = this->m_LeftDefaultBoxSize;
		const spe::Vector2 pos = spe::Vector2(this->m_ptr_Player->Transform.GetPosition().X + PLAYER_SPEED * spe::Time::s_DeltaTime,
			this->m_ptr_Player->Transform.GetPosition().Y);
		this->m_ptr_Player->Transform.SetPosition(pos);
	}
}

void PlayerController::Jump()
{
	this->m_Grounded = this->m_ptr_Player->Collider.CollidedWithTag("Floor") != nullptr;

	if (spe::Input::OnKeyPress(spe::KeyBoardCode::Space) && this->m_Grounded)
	{
		this->m_Grounded = false;
		this->m_ptr_Player->Physicsbody.Velocity.Y = 0;
		spe::Physics::AddForce(this->m_ptr_Player, spe::Vector2(0, 1), 400);
	}
}
void PlayerController::DownAttack()
{
	if (spe::Input::OnKeyPress(spe::KeyBoardCode::S))
	{
		this->m_DownAttacking = true;
		this->m_ptr_Player->Physicsbody.Velocity.Y = DOWN_ATTACK_SPEED;
	}
	if (this->m_Grounded)
	{
		this->m_DownAttacking = false;
	}
}