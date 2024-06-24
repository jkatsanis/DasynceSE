#include "EnemyHandler.h"

void EnemyHandler::Start(spe::EngineConfig& cnfg)
{
	this->m_MonkeyBehaviour.Start(cnfg);
}

void EnemyHandler::Update()
{
	this->m_MonkeyBehaviour.Update();
}

