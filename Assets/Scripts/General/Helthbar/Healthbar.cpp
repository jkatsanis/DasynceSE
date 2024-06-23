#include "Healthbar.h"

void Healthbar::Start(int health, spe::EngineConfig& cnfg)
{
	this->m_HealthBar = spe::PrefabRepository::GetPrefabByName("Healthbar");

	if (this->m_HealthBar == nullptr)
	{
		spe::Log::LogString("[ERROR] Couldnt find prefab file somethingf idk shit");
		return;
	}

	cnfg.SetNoDeleteOnSceneSwap(this->m_HealthBar);
	this->m_Health = health;
	this->m_TotalHealth = health;

	this->m_HealthRect = this->m_HealthBar->ptr_Childs[0];

	cnfg.ptr_Sprites->Add(this->m_HealthBar);

	spe::Sprite* player = cnfg.ptr_Sprites->GetByName("Player");
	player->ptr_Childs.push_back(this->m_HealthBar);
	this->m_HealthBar->Transform.SetPosition(spe::Vector2(this->m_HealthBar->Transform.GetPosition().X, this->m_HealthBar->Transform.GetPosition().Y + 150));
}

void Healthbar::Damage(int health)	 
{
	if (this->m_Health <= 0)
	{
		// Die
		return;
	}
	if (health == 0)
	{
		return;
	}

	this->m_Health -= health;

	sf::Sprite& spr = this->m_HealthRect->GetSprite();
	sf::Texture& foregroundTexture = this->m_HealthRect->GetTexture();
	
	float healthPercentage = static_cast<float>(this->m_Health) / this->m_TotalHealth;

	sf::IntRect foregroundRect = spr.getTextureRect();
	foregroundRect.width = static_cast<int>(foregroundTexture.getSize().x * healthPercentage);
	spr.setTextureRect(foregroundRect);
}
