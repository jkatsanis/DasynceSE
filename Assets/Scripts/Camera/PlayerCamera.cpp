#include "PlayerCamera.h"

void PlayerCamera::Start(spe::Camera* ptr, const spe::Sprite* pl)
{
	this->m_ptr_Camera = ptr;
	this->m_ptr_Player = pl;
	this->m_Timer = 0.0f;
}

void PlayerCamera::Update()
{
	this->m_Timer += spe::Time::s_DeltaTime;
	if (this->m_Timer < 0.002f)
	{
		return;
	}
	this->m_Timer = 0.0f;

	spe::Vector2 playerPos = spe::Vector2(this->m_ptr_Player->Transform.GetPosition().X, this->m_ptr_Player->Transform.GetPosition().Y + 100);
	playerPos.Y *= -1;


	const float smoothingFactor = 0.025f; // Adjust this value for desired smoothness
	spe::Vector2 targetCameraPos = spe::Physics::Lerp(this->m_ptr_Camera->Position, playerPos, smoothingFactor);
    this->m_ptr_Camera->Position = targetCameraPos;
}

