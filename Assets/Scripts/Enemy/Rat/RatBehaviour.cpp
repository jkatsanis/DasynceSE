#include "RatBehaviour.h"


void RatBehaviour::Start(spe::EngineConfig& cnfg, const std::string& scene)
{
	(void)scene;
	this->m_ptr_Config = &cnfg;
	// Spawning gets handled in the scene files for example LevelUI.cpp
}

void RatBehaviour::Update()
{
	auto remove_if_dead = [this](size_t index) -> bool {
		if (!this->m_Rats[index].HasDied())
		{
			return false;
		}

		spe::Sprite* sprite = this->m_Rats[index].GetSprite();
		if (sprite != nullptr && this->m_ptr_Config != nullptr)
		{
			this->m_ptr_Config->ptr_Sprites->DeleteWithName(sprite->Name);
		}
		this->m_Rats.erase(this->m_Rats.begin() + index);
		return true;
	};

	for (size_t i = 0; i < this->m_Rats.size();)
	{
		// Check before and after update to remove enemies that die mid-frame.
		if (remove_if_dead(i))
		{
			continue;
		}

		this->m_Rats[i].Update();

		if (remove_if_dead(i))
		{
			continue;
		}

		i++;
	}
}


void RatBehaviour::Spawn(const spe::Vector2& position)
{
	Rat ra;

	spe::Sprite* rat = spe::PrefabRepository::GetPrefabByName("Rat_2");
	rat->Transform.SetPosition(position);
	rat->Name = "Rat " + std::to_string(this->m_Rats.size());

	this->m_ptr_Config->ptr_Sprites->Add(std::move(rat));

	ra.Start(*this->m_ptr_Config, rat);

	this->m_Rats.push_back(std::move(ra));
	

}

void RatBehaviour::OnSceneChange()
{
	this->m_Rats.clear();
}

bool RatBehaviour::DamageBySprite(spe::Sprite* sprite, int damage)
{
	for (size_t i = 0; i < this->m_Rats.size(); i++)
	{
		if (this->m_Rats[i].GetSprite() == sprite)
		{
			this->m_Rats[i].TakeDamage(damage);
			return true;
		}
	}
	return false;
}
