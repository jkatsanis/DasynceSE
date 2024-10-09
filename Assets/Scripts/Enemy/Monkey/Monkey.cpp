#include "Monkey.h"

// Private

void Monkey::Start(spe::EngineConfig& config, spe::Sprite* sprite)
{
	this->m_AttackCooldown = 0.0f;
	this->m_MonkeySprite = sprite;
	this->m_Healthbar.Start(100, config, this->m_MonkeySprite);
}

void Monkey::Attack()
{
	if (this->m_ApplyForce && this->m_ForceCooldown >= 0.2f)
	{
		PlayerController& controller = PlayerController::GetInstance();
		int32_t direction = 1;

		if (spe::GameUtils::IsLeft(controller.ptr_Player, this->m_MonkeySprite))
		{
			direction = -1;
		}

		spe::Physics::AddForce(controller.ptr_Player, spe::Vector2((float)direction, 0.0f), 2000);
		this->m_ApplyForce = false;
		this->m_ForceCooldown = 0.0f;
		return;
	}
	this->m_ForceCooldown += spe::Time::s_DeltaTime;

	if (!this->m_MonkeySprite->Collider.Collided)
	{
		return;
	}
	if (this->m_MonkeySprite->Collider.CollidedWithTag("Player")
		&& this->m_AttackCooldown >= ATTACK_COOLDOWN)
	{
		PlayerController& controller = PlayerController::GetInstance();

		this->m_AttackCooldown = 0.0f;

		this->m_MonkeySprite->Animator.Play("attack");

		if (controller.ptr_Player->Physicsbody.Velocity.X < 500)
		{
			this->m_ApplyForce = true;
			this->m_ForceCooldown = 0.0f;
		}


		controller.HealthBar.Damage(5);
	}
}

// Public

void Monkey::Update()
{
	this->m_AttackCooldown += spe::Time::s_DeltaTime;

	spe::Sprite* player = PlayerController::GetInstance().ptr_Player;

	if (!this->m_MonkeySprite->Process)
	{
		return;
	}

	const float CHANGED_POS = MONKEY_SPEED * spe::Time::s_DeltaTime;
	if (player->Transform.GetPosition().X > this->m_MonkeySprite->Transform.GetPosition().X)
	{
		this->m_MonkeySprite->Transform.SetScale(spe::Vector2(-4, 4));

		const float POS_X = this->m_MonkeySprite->Transform.GetPosition().X + CHANGED_POS;
		this->m_MonkeySprite->Transform.SetPosition(spe::Vector2(POS_X, this->m_MonkeySprite->Transform.GetPosition().Y));
	}
	else if (player->Transform.GetPosition().X < this->m_MonkeySprite->Transform.GetPosition().X)
	{
		this->m_MonkeySprite->Transform.SetScale(spe::Vector2(4, 4));

		const float POS_X = this->m_MonkeySprite->Transform.GetPosition().X - CHANGED_POS;
		this->m_MonkeySprite->Transform.SetPosition(spe::Vector2(POS_X, this->m_MonkeySprite->Transform.GetPosition().Y));
	}

	this->Attack();
}

