#include "Monkey.h"

void Monkey::Start(spe::EngineConfig& config)
{
	this->m_Healthbar.Start(100, config, this->m_MonkeySprite);
}

void Monkey::Update(const spe::Vector2& player_pos)
{
	if (!this->m_MonkeySprite->Process)
	{
		return;
	}

	const float CHANGED_POS = MONKEY_SPEED * spe::Time::s_DeltaTime;
	if (player_pos.X > this->m_MonkeySprite->Transform.GetPosition().X)
	{
		this->m_MonkeySprite->Transform.SetScale(spe::Vector2(-4, 4));

		const float POS_X = this->m_MonkeySprite->Transform.GetPosition().X + CHANGED_POS;
		this->m_MonkeySprite->Transform.SetPosition(spe::Vector2(POS_X, this->m_MonkeySprite->Transform.GetPosition().Y));
	}
	else if (player_pos.X < this->m_MonkeySprite->Transform.GetPosition().X)
	{
		this->m_MonkeySprite->Transform.SetScale(spe::Vector2(4, 4));

		const float POS_X = this->m_MonkeySprite->Transform.GetPosition().X - CHANGED_POS;
		this->m_MonkeySprite->Transform.SetPosition(spe::Vector2(POS_X, this->m_MonkeySprite->Transform.GetPosition().Y));
	}
}

