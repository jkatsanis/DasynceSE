#include "EnemyHandler.h"

void EnemyHandler::Start(spe::EngineConfig& cnfg)
{
	this->m_MonkeyBehaviour.Start(cnfg);
}

void EnemyHandler::Update()
{
	this->m_MonkeyBehaviour.Update();
}

void EnemyHandler::OnSceneChange()
{
	this->m_MonkeyBehaviour.OnSceneChange();
}

