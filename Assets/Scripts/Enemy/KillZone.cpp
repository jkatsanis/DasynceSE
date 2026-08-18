#include "KillZone.h"

#include "Scripts/Player/PlayerController.h"

void KillZone::Start(spe::EngineConfig& config)
{
    m_Player = PlayerController::GetInstance().ptr_Player;
    config.ptr_Sprites->GetSpritesByTag("KillZone", m_KillZone);
}

void KillZone::Update()
{
    if (!m_KillZone.empty() && m_KillZone[0]->Collider.CollidedWithName(m_Player->Name))
    {
        m_Player->Transform.Teleport(spe::Vector2(-950, -125.381f));
    }
}