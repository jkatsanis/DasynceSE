#include "Healthbar.h"

void Healthbar::DontDeleteOnSceneSwap(spe::EngineConfig& cnfg)
{
	cnfg.DontDeleteOnSceneSwap(this->m_HealthBar); // Works recursivly! 
}

void Healthbar::Start(int health, spe::EngineConfig& cnfg, spe::Sprite* to)
{
	this->m_Health = health;
	this->m_TotalHealth = health;

	this->m_HealthBar = spe::PrefabRepository::GetPrefabByName("Healthbar");

	if (this->m_HealthBar == nullptr)
	{
		spe::Log::LogString("[ERROR] Couldnt find prefab file somethingf idk shit");
		return;
	}

	this->m_HealthRect = this->m_HealthBar->ptr_Childs[0];

	this->m_HealthRect->Name = "HealthRect " + std::to_string(Healthbar::s_m_TotalHealthBars);
	this->m_HealthBar->Name = "Healthbar " + std::to_string(Healthbar::s_m_TotalHealthBars);

	cnfg.ptr_Sprites->Add(this->m_HealthBar);

	this->m_HealthBar->SetParent(to);

	this->m_HealthBar->Transform.SetPosition(spe::Vector2(this->m_HealthBar->Transform.GetPosition().X, this->m_HealthBar->Transform.GetPosition().Y + 150));

	Healthbar::s_m_TotalHealthBars++;
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

int Healthbar::s_m_TotalHealthBars = 0;