#include "ComputerRoom.h"

void ComputerRoom::Start(spe::EngineConfig& config)
{
	this->m_ptr_Player = config.ptr_Sprites->GetByName("Player");
}

void ComputerRoom::Update(std::function<void(const std::string&)> OnSceneChange)
{

	if (this->m_ptr_Player->Collider.Collided)
	{
		spe::Sprite* spr = this->m_ptr_Player->Collider.CollidedWithTag("kanal-teleport");
		if (spr != nullptr)
		{
			OnSceneChange("scene 1");

			this->m_ptr_Player->Transform.Teleport(KANAL_TP_POSITION);
		}
	}
}

