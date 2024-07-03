#include "Monkey.h"

// Private

void Monkey::Start(spe::EngineConfig& config, spe::Sprite* sprite)
{
	this->m_MonkeySprite = sprite;
	this->m_Healthbar.Start(100, config, this->m_MonkeySprite);
}

void Monkey::Attack(spe::Sprite* player)
{
	if (this->m_MonkeySprite->Collider.CollidedWithTag("Player"))
	{
		player->Physicsbody.Friction = 6;
		this->m_MonkeySprite->Animator.Play("attack");

		int32_t direction = 1;

		if (spe::GameUtils::IsLeft(player, this->m_MonkeySprite))
		{
			direction = -1;
		}

		spe::Physics::AddForce(player, spe::Vector2(direction, 0), 500);

		std::cout << "saug";
	}
}

// Public

void Monkey::Update(spe::Sprite* player)
{
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

	this->Attack(player);
}

