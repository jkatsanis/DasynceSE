#include "EnemyHandler.h"

void EnemyHandler::Start(spe::EngineConfig& cnfg, const std::string& scene)
{
	this->MonkeyBehaviourObject.Start(cnfg, scene);
	this->RatBehaviourObject.Start(cnfg, scene);
}

void EnemyHandler::Update()
{
	this->MonkeyBehaviourObject.Update();
	this->RatBehaviourObject.Update();
}

void EnemyHandler::OnSceneChange()
{
	this->MonkeyBehaviourObject.OnSceneChange();
	this->RatBehaviourObject.OnSceneChange();
}

bool EnemyHandler::DamageEnemyBySprite(spe::Sprite* sprite, int damage)
{
	if (this->MonkeyBehaviourObject.DamageBySprite(sprite, damage))
	{
		return true;
	}
	if (this->RatBehaviourObject.DamageBySprite(sprite, damage))
	{
		return true;
	}
	return false;
}

EnemyHandler EnemyHandler::m_Instance = EnemyHandler();
