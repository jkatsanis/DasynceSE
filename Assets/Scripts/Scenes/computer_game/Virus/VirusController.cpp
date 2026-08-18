#include "VirusController.h"


void VirusController::Start(spe::EngineConfig& cnfg)
{
	this->m_ptr_Config = &cnfg;
	this->m_ptr_Virus = cnfg.ptr_Sprites->GetByName("Virus");
	this->m_ptr_Player = cnfg.ptr_Sprites->GetByName("PlayerPx");

	this->m_LaserTimer = 0.0f;
	this->m_teleportCounter = 0.0f;
	this->m_LaserTimerCap = 1.0f;

	this->m_VirusSpeed = 0.1f;
	this->Hearts = 3;

	this->m_Lasers.clear();
}

void VirusController::Update(std::function<void()> OnPlayerHit, std::function<void(spe::Sprite* laser, int32_t laser_speed)> OnShieldHit)
{
	const static int ROTATION_SPEED = 1500;
	const static int LASER_SPEED = 1500;

	const uint32_t angle = this->m_ptr_Virus->Transform.GetRotation() + (uint32_t)(ROTATION_SPEED * spe::Time::s_DeltaTime);
	this->m_ptr_Virus->Transform.SetRotation(angle);
	spe::Log::LogString(std::to_string(angle));

	this->m_teleportCounter += spe::Time::s_DeltaTime;


	this->Move();

	this->m_LaserTimer += spe::Time::s_DeltaTime;

	if (this->m_LaserTimer >= m_LaserTimerCap)
	{
		this->m_LaserTimer = 0.0f;
		spe::Sprite* laser = spe::PrefabRepository::GetPrefabByName("VirusLaser");

		laser->Transform.SetPosition(this->m_ptr_Virus->Transform.GetPosition());
		this->m_ptr_Config->ptr_Sprites->Add(laser);

		this->m_Lasers.push_back(laser);

		spe::Physics::AddForce(laser, 
			spe::Vector2::GetDirection(laser->Transform.GetPosition(), this->m_ptr_Player->Transform.GetPosition()), LASER_SPEED);

	}

	for (size_t i = 0; i < m_Lasers.size(); i++)
	{
		spe::Sprite* laser = m_Lasers[i];

		if (laser->Transform.GetPosition().X < -1200
			|| laser->Transform.GetPosition().X > 1200)
		{
			// Delete the object if necessary
			this->m_ptr_Config->ptr_Sprites->DeleteWithName(laser->Name);
			m_Lasers.erase(m_Lasers.begin() + i);
			return;
		}
		if (laser->Collider.CollidedWithName("PlayerPx"))
		{
			this->m_ptr_Config->ptr_Sprites->DeleteWithName(laser->Name);
			m_Lasers.erase(m_Lasers.begin() + i);
			OnPlayerHit();
			return;
		}
		if (laser->Collider.CollidedWithName("CyberShield"))
		{
			OnShieldHit(laser, LASER_SPEED);
			return;
		}
		if (laser->Collider.CollidedWithName("Virus") && laser->Tag == "laser")
		{
			this->m_ptr_Config->ptr_Sprites->DeleteWithName(laser->Name);
			m_Lasers.erase(m_Lasers.begin() + i);
			this->Hearts--;
		}		
	}

	if (this->m_teleportCounter >= 1.5f)
	{
		this->m_teleportCounter = 0.0f;
		this->m_ptr_Virus->Transform.Teleport(
			spe::Vector2((float)spe::GameUtils::Random(-800, 800), (float)spe::GameUtils::Random(-400, 400)));
	}
}


void VirusController::Move()
{
	const spe::Vector2 pos = this->m_ptr_Virus->Transform.GetPosition();
	const spe::Vector2 playerPos = this->m_ptr_Player->Transform.GetPosition();
	const float change = m_VirusSpeed * spe::Time::s_DeltaTime;

	// Calculate the direction vector from the virus to the player
	spe::Vector2 direction = playerPos - pos;

	// Normalize the direction vector
	direction.Normalize();

	// Update the virus's position by moving it towards the player
	spe::Vector2 newPos = pos + direction * change;

	// Set the new position
	this->m_ptr_Virus->Transform.SetPosition(newPos);
}

