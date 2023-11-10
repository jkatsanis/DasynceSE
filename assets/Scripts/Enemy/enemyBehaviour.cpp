#include "enemyBehaviour.h"

void EnemyBehaviour::start(s2d::EngineConfig& config)
{
	m_ptr_enemy = config.ptr_sprites->getSpriteWithName("Rat");
	m_ptr_enemy->animator.play("Walk");
}

void EnemyBehaviour::update()
{
	const s2d::Vector2 pos = s2d::Vector2(this->m_ptr_enemy->transform.getPosition().x - 500 * s2d::Time::s_delta_time,
		this->m_ptr_enemy->transform.getPosition().y);
	m_ptr_enemy->transform.setPosition(pos);
}