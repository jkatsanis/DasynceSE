#include "Rat.h"

void Rat::Start(spe::EngineConfig& config, spe::Sprite* sprite)
{
	this->m_EnemySprite = sprite;
	this->m_Healthbar.Start(100, config, this->m_EnemySprite);
	this->m_InRange = false;	
	this->m_AttackCooldown = 0.0f;
	this->m_EnemySprite->Animator.Play("Idle");
}

void Rat::Update()
{
	spe::Sprite* player = PlayerController::GetInstance().ptr_Player;
	if (!spe::GameUtils::IsInRangeX(player, this->m_EnemySprite, 500))
	{
		if (this->m_InRange)
		{
			this->m_EnemySprite->Animator.Play("Idle");
		}
		this->m_InRange = false;
		return;
	}
	if (!this->m_InRange)
	{
		this->m_InRange = true;
		this->m_EnemySprite->Animator.Play("Attack");
	}



	const float CHANGED_POS = RAT_SPEED * spe::Time::s_DeltaTime;
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


void Rat::Attack()
{
	this->m_AttackCooldown += spe::Time::s_DeltaTime;

	if (this->m_EnemySprite->Collider.CollidedWithTag("Player")
		&& this->m_AttackCooldown >= RAT_2_ATTACK_COOLDOWN)
	{
		PlayerController& controller = PlayerController::GetInstance();

		this->m_AttackCooldown = 0.0f;
		float direction = 1;
		if (spe::GameUtils::IsLeft(controller.ptr_Player, this->m_EnemySprite))
		{
			direction = -1;
		}

		spe::Physics::AddForce(controller.ptr_Player, spe::Vector2(direction, 0), 200);
		spe::Physics::AddForce(controller.ptr_Player, spe::Vector2(0, 1), 100);


		controller.HealthBar.Damage(5);
	}
}

void Rat::TakeDamage(int damage)
{
	this->m_Healthbar.Damage(damage);
}

