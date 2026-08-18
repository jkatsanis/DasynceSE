#include "Monkey.h"

// Private

void Monkey::Start(spe::EngineConfig& config, spe::Sprite* sprite)
{
	this->m_EnemySprite = sprite;
	this->m_Healthbar.Start(100, config, this->m_EnemySprite);
	this->m_InRange = true;
}

void Monkey::Attack()
{
	this->m_AttackCooldown += spe::Time::s_DeltaTime;

	if (this->m_ApplyForce && this->m_ForceCooldown >= 0.2f)
	{
		PlayerController& controller = PlayerController::GetInstance();

		float direction = 1;

		if (spe::GameUtils::IsLeft(controller.ptr_Player, this->m_EnemySprite))
		{
			direction = -1;
		}

		spe::Physics::AddForce(controller.ptr_Player, spe::Vector2(direction, 0), 2000);
		this->m_ApplyForce = false;
		this->m_ForceCooldown = 0.0f;
		return;
	}
	this->m_ForceCooldown += spe::Time::s_DeltaTime;

	if (!this->m_EnemySprite->Collider.Collided)
	{
		return;
	}
	if (this->m_EnemySprite->Collider.CollidedWithTag("Player")
		&& this->m_AttackCooldown >= MONKEY_ATTACK_COOLDOWN)
	{
		PlayerController& controller = PlayerController::GetInstance();

		this->m_AttackCooldown = 0.0f;

		this->m_EnemySprite->Animator.Play("attack");

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
	if (!this->m_EnemySprite->Process)
	{
		return;
	}

	spe::Sprite* player = PlayerController::GetInstance().ptr_Player;

	if (!spe::GameUtils::IsInRangeX(player, this->m_EnemySprite, 370))
	{
		if (this->m_InRange)
		{
			this->m_EnemySprite->Animator.Play("idle");
		}
		this->m_InRange = false;
		return;
	}
	// Else play walk


	const float CHANGED_POS = MONKEY_SPEED * spe::Time::s_DeltaTime;
	if (player->Transform.GetPosition().X > this->m_EnemySprite->Transform.GetPosition().X)
	{
		this->m_EnemySprite->Transform.SetScale(spe::Vector2(-4, 4));

		const float POS_X = this->m_EnemySprite->Transform.GetPosition().X + CHANGED_POS;
		this->m_EnemySprite->Transform.SetPosition(spe::Vector2(POS_X, this->m_EnemySprite->Transform.GetPosition().Y));
	}
	else if (player->Transform.GetPosition().X < this->m_EnemySprite->Transform.GetPosition().X)
	{
		this->m_EnemySprite->Transform.SetScale(spe::Vector2(4, 4));

		const float POS_X = this->m_EnemySprite->Transform.GetPosition().X - CHANGED_POS;
		this->m_EnemySprite->Transform.SetPosition(spe::Vector2(POS_X, this->m_EnemySprite->Transform.GetPosition().Y));
	}

	this->Attack();
}

void Monkey::TakeDamage(int damage)
{
	this->m_Healthbar.Damage(damage);
}

