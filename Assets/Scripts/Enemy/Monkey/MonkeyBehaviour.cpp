#include "MonkeyBehaviour.h"

// Public

void MonkeyBehaviour::Start(spe::EngineConfig& cnfg, const std::string& scene)
{
	(void)scene;
	this->m_ptr_Config = &cnfg;
}

void MonkeyBehaviour::Update()
{
	auto remove_if_dead = [this](size_t index) -> bool {
		if (!this->m_Monkeys[index].HasDied())
		{
			return false;
		}

		spe::Sprite* sprite = this->m_Monkeys[index].GetSprite();
		if (sprite != nullptr && this->m_ptr_Config != nullptr)
		{
			this->m_ptr_Config->ptr_Sprites->DeleteWithName(sprite->Name);
		}
		this->m_Monkeys.erase(this->m_Monkeys.begin() + index);
		return true;
	};

	for (size_t i = 0; i < this->m_Monkeys.size();)
	{
		// Check before and after update to remove enemies that die mid-frame.
		if (remove_if_dead(i))
		{
			continue;
		}

		this->m_Monkeys[i].Update();

		if (remove_if_dead(i))
		{
			continue;
		}

		i++;
	}
}

void MonkeyBehaviour::Spawn(const spe::Vector2& position)
{
	Monkey mon;

	spe::Sprite* monkey = spe::PrefabRepository::GetPrefabByName("Monkey");
	monkey->Transform.SetPosition(position);
	monkey->Name = "Monkey " + std::to_string(this->m_Monkeys.size());

	this->m_ptr_Config->ptr_Sprites->Add(monkey);

	mon.Start(*this->m_ptr_Config, monkey);

	this->m_Monkeys.push_back(std::move(mon));
}

void MonkeyBehaviour::OnSceneChange()
{
	this->m_Monkeys.clear();
}

bool MonkeyBehaviour::DamageBySprite(spe::Sprite* sprite, int damage)
{
	for (size_t i = 0; i < this->m_Monkeys.size(); i++)
	{
		if (this->m_Monkeys[i].GetSprite() == sprite)
		{
			this->m_Monkeys[i].TakeDamage(damage);
			return true;
		}
	}
	return false;
}

// Private
