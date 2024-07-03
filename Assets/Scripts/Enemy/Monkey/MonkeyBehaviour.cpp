#include "MonkeyBehaviour.h"

// Public

void MonkeyBehaviour::Start(spe::EngineConfig& cnfg)
{
	this->m_ptr_Config = &cnfg;
	this->m_ptr_Player = this->m_ptr_Config->ptr_Sprites->GetByName("Player");

	// Spawn monkeys
	this->SpawnMonkey(spe::Vector2(0, 0));
}

void MonkeyBehaviour::Update()
{
	for (size_t i = 0; i < this->m_Monkeys.size(); i++)
	{
		this->m_Monkeys[i].Update(this->m_ptr_Player);
	}
}

void MonkeyBehaviour::SpawnMonkey(const spe::Vector2& position)
{
	Monkey mon;

	spe::Sprite* monkey = spe::PrefabRepository::GetPrefabByName("Monkey");
	monkey->Transform.SetPosition(position);
	monkey->Name = "Monkey " + std::to_string(this->m_Monkeys.size());

	this->m_ptr_Config->ptr_Sprites->Add(monkey);
	mon.Start(*this->m_ptr_Config, monkey);

	this->m_Monkeys.push_back(std::move(mon));
}

// Private