#include "ComputerGame.h"

void ComputerGame::Start(spe::EngineConfig& cnfg)
{
	cnfg.ptr_Camera->Position = spe::Vector2(0, 0);
	cnfg.ptr_Camera->SetZoom(1.4f);
	cnfg.ptr_Sprites->GetByName("Cursor")->Animator.Play("Blinker");

	this->ptr_PlayerPx = cnfg.ptr_Sprites->GetByName("PlayerPx");
	this->ptr_Shield = cnfg.ptr_Sprites->GetByName("CyberShield");

	this->m_VController.Start(cnfg);

	this->m_Health = 3;
}

void ComputerGame::Update(std::function<void(const std::string&)> OnSceneChange)
{
	ImGui::Text("[ESC] To escape");
	this->DisplayHealth();

	this->m_VController.Update(
		[this]
		{
			this->OnPlayerHit();
		},
		[this](spe::Sprite* laser, int32_t laser_speed)
		{
			this->OnShieldHit(laser, laser_speed);
		}
	);

	if (spe::Input::OnKeyRelease(spe::KeyBoardCode::Escape)
		|| this->m_Health <= 0 || this->m_VController.Hearts <= 0)
	{
		OnSceneChange("computer_room");
	}

	this->PlayerMovement();
	this->ShieldMovement();
}

void ComputerGame::DisplayHealth()
{
	UI::SetFontScale(D_SCALE + 1.0f);
	UI::SetCursor(spe::Vector2(-425, 335));
	ImGui::Text(std::to_string(this->m_Health).c_str());

	UI::SetFontScale(D_SCALE + 1.0f);
	UI::SetCursor(spe::Vector2(-425, 432));
	ImGui::Text(std::to_string(this->m_VController.Hearts).c_str());
}

void ComputerGame::PlayerMovement()
{
	const static int PLAYER_MOVEMENT_GAP = 1000;

	// Move player left with 'A' key
	if (spe::Input::OnKeyHold(spe::KeyBoardCode::A))
	{
		ptr_PlayerPx->Transform.SetPosition(
			spe::Vector2(ptr_PlayerPx->Transform.GetPosition().X - PLAYER_MOVEMENT_GAP * spe::Time::s_DeltaTime,
				ptr_PlayerPx->Transform.GetPosition().Y));
	}

	// Move player up with 'W' key
	if (spe::Input::OnKeyHold(spe::KeyBoardCode::W))
	{
		ptr_PlayerPx->Transform.SetPosition(
			spe::Vector2(ptr_PlayerPx->Transform.GetPosition().X,
				ptr_PlayerPx->Transform.GetPosition().Y + PLAYER_MOVEMENT_GAP * spe::Time::s_DeltaTime));
	}

	// Move player down with 'S' key
	if (spe::Input::OnKeyHold(spe::KeyBoardCode::S))
	{
		ptr_PlayerPx->Transform.SetPosition(
			spe::Vector2(ptr_PlayerPx->Transform.GetPosition().X,
				ptr_PlayerPx->Transform.GetPosition().Y - PLAYER_MOVEMENT_GAP * spe::Time::s_DeltaTime));
	}

	// Move player right with 'D' key
	if (spe::Input::OnKeyHold(spe::KeyBoardCode::D))
	{
		ptr_PlayerPx->Transform.SetPosition(
			spe::Vector2(ptr_PlayerPx->Transform.GetPosition().X + PLAYER_MOVEMENT_GAP * spe::Time::s_DeltaTime,
				ptr_PlayerPx->Transform.GetPosition().Y));
	}

}

void ComputerGame::ShieldMovement()
{
	const static int CYPER_SHIELD_SPEED = 1000;

	// Move player up with 'W' key or Up Arrow
	if (spe::Input::OnKeyHold(spe::KeyBoardCode::Up))
	{
		ptr_Shield->Transform.SetPosition(
			spe::Vector2(ptr_Shield->Transform.GetPosition().X,
				ptr_Shield->Transform.GetPosition().Y + CYPER_SHIELD_SPEED * spe::Time::s_DeltaTime));
	}

	// Move player down with 'S' key or Down Arrow
	if (spe::Input::OnKeyHold(spe::KeyBoardCode::Down))
	{
		ptr_Shield->Transform.SetPosition(
			spe::Vector2(ptr_Shield->Transform.GetPosition().X,
				ptr_Shield->Transform.GetPosition().Y - CYPER_SHIELD_SPEED * spe::Time::s_DeltaTime));
	}

	// Move player left with 'A' key or Left Arrow
	if (spe::Input::OnKeyHold(spe::KeyBoardCode::Left))
	{
		ptr_Shield->Transform.SetPosition(
			spe::Vector2(ptr_Shield->Transform.GetPosition().X - CYPER_SHIELD_SPEED * spe::Time::s_DeltaTime,
				ptr_Shield->Transform.GetPosition().Y));
	}

	// Move player right with 'D' key or Right Arrow
	if (spe::Input::OnKeyHold(spe::KeyBoardCode::Right))
	{
		ptr_Shield->Transform.SetPosition(
			spe::Vector2(ptr_Shield->Transform.GetPosition().X + CYPER_SHIELD_SPEED * spe::Time::s_DeltaTime,
				ptr_Shield->Transform.GetPosition().Y));
	}

	if (spe::Input::OnKeyPress(spe::KeyBoardCode::Space))
	{
		ptr_Shield->Transform.SetRotation(ptr_Shield->Transform.GetRotation() + 90); 
	}
}


void ComputerGame::OnPlayerHit()
{
	this->m_Health--;
}

void ComputerGame::OnShieldHit(spe::Sprite* laser, int32_t laser_speed)
{
	const spe::Vector2 pos = laser->Transform.GetPosition();
	const spe::Vector2 playerPos = this->m_VController.GetVirus()->Transform.GetPosition();

	// Calculate the direction vector from the virus to the player
	spe::Vector2 direction = playerPos - pos;

	// Normalize the direction vector

	laser->Tag = "laser";

	direction.Normalize();
	laser->Physicsbody.Velocity = spe::Vector2(0, 0);
	spe::Physics::AddForce(laser, direction, (float)laser_speed);
}
