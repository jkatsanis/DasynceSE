#include "MachineryRoom.h"

void MachineryRoom::Start(spe::EngineConfig& cnfg)
{
	spe::Sprite* player = cnfg.ptr_Sprites->GetByName("Player");
	this->m_ptr_Player = player;
	player->Transform.SetPosition(spe::Vector2(-989.756f, -217.774f));
	this->m_ptr_Back = cnfg.ptr_Sprites->GetByName("Back");
	//this->Leaving = false;
	this->m_conveyorSound.Configure("Assets/Audio/Sounds/conveyor.mp3", spe::Audio::AudioType::SOUND, "Conveyor Belt");
	this->m_conveyorSound.SetRelativeToListener(false);
	this->m_conveyorSound.SetPosition(-350.0f, -200.0f);
	this->m_conveyorSound.SetMinDistance(450.0f);
	this->m_conveyorSound.SetAttenuation(3.0f);
	this->m_conveyorSound.SetVolume(100.0f);
	this->m_conveyorSound.SetLoop(true);
	this->m_conveyorSound.Load();
	this->m_conveyorSound.Play();

	this->m_ptr_Door = cnfg.ptr_Sprites->GetByName("Door");

	this->m_ptr_Door->Animator.CreateReversedAnimation("open", "close");

	m_ptr_DoorLevelOne = cnfg.ptr_Sprites->GetByName("LevelOne");
	this->m_ptr_DoorLevelOne->Animator.CreateReversedAnimation("open", "close");
}

void MachineryRoom::Update(std::function<void(const std::string&)> OnSceneChange)
{
	static bool leavingForLevel1 = false;
	if (this->m_ptr_Door->Animator.GetAnimationPlaying().IsPlaying)
	{
		//this->Leaving = false;
		this->m_conveyorSound.Stop();
		OnSceneChange("computer_room");
	}

	if (leavingForLevel1 && !this->m_ptr_DoorLevelOne->Animator.GetAnimationPlaying().IsPlaying)
	{
		leavingForLevel1 = false;
		this->m_conveyorSound.Stop();
		OnSceneChange("StoreRoom");
	}

	if (this->m_ptr_Player->Collider.Collided)
	{
		UI::SetFontScale(D_SCALE + 2.0f);

		if (this->m_ptr_Player->Collider.CollidedWithName("Back"))
		{

			if (UI::Button("Go To Computer Room [W]", this->m_ptr_Back)
				|| spe::Input::OnKeyRelease(spe::KeyBoardCode::W))
			{
				this->m_ptr_Door->SetSpriteTexture("Assets\\Sprites\\Enviroment\\ComputerRoom\\Door\\open_3.png");
				this->m_ptr_Door->Animator.Play("open");

				// Change scene and stop sound
			}

			return;
		}


		if (this->m_ptr_Player->Collider.CollidedWithName("LevelOne"))
		{

			if (UI::Button("Go Back to First Scene [W]", this->m_ptr_DoorLevelOne)
				|| spe::Input::OnKeyRelease(spe::KeyBoardCode::W))
			{
				leavingForLevel1 = true;
				this->m_ptr_DoorLevelOne->SetSpriteTexture("Assets\\Sprites\\Enviroment\\ComputerRoom\\Door\\open_3.png");
				this->m_ptr_DoorLevelOne->Animator.Play("open");

				// Change scene and stop sound
			}

			return;
		}
	}
}

