#include "ComputerRoom.h"
#include "Audio/Audio.h"

void ComputerRoom::Start(spe::EngineConfig& config)
{
	this->m_ptr_Player = config.ptr_Sprites->GetByName("Player");
	this->m_ptr_Server = config.ptr_Sprites->GetByName("Server");
	this->m_IsEneryOn = false;
	this->m_FlipMessage = "[F] Flip Lever";
	this->m_ptr_Config = &config;
	this->m_IsDoorOpen = false;
	// this->m_EnergySound.Configure("Assets/Audio/Sounds/generator_boot.mp3", spe::Audio::AudioType::SOUND, "Generator Booting Up");
	// this->m_EnergySound.SetRelativeToListener(false);
	// this->m_EnergySound.SetVolume(60);
	// this->m_EnergySound.SetMinDistance(350.0f); // min distance sets how far it is hearable and ...
	// this->m_EnergySound.SetAttenuation(4.0f); // attenuation how fast it fades out over the min distance
	// this->m_EnergySound.SetPosition(666.37f, -228.11f);
	// this->m_EnergySound.Load();

	spe::Sprite* door = this->m_ptr_Config->ptr_Sprites->GetByName("Door");

	door->Animator.CreateReversedAnimation("open", "close");
}

void ComputerRoom::Update(std::function<void(const std::string&)> OnSceneChange)
{
	bool collided = this->m_ptr_Player->Collider.Collided;

	if (this->m_IsEneryOn && this->m_FlipMessage != "[F] Flip Lever")
	{
		this->m_FlipMessage = "[F] Flip Lever";
	}

	if (collided && this->m_IsDoorOpen)
	{
		spe::Sprite* spr = this->m_ptr_Player->Collider.CollidedWithName("Door_Handle");

		if (spr != nullptr)
		{
			UI::SetFontScale(D_SCALE + 2.0f);
			if (UI::Button("[W] Go to machinery room", spr) || spe::Input::OnKeyRelease(spe::KeyBoardCode::W))
			{
				this->m_ptr_Server->Audio.GetAudioByName("GeneratorBoot")->Stop();
				this->m_ptr_Server->Particles.Stop();
				OnSceneChange("MachineryRoom");
			}
		}

		return;
	}

 	if (collided)
	{
		spe::Sprite* spr = this->m_ptr_Player->Collider.CollidedWithTag("kanal-teleport");
		if (spr != nullptr)
		{
			OnSceneChange("scene 1");

			this->m_ptr_Player->Transform.Teleport(KANAL_TP_POSITION);

			return;
		}
	}

    if (collided)
	{
		spe::Sprite* spr = this->m_ptr_Player->Collider.CollidedWithName("Door_Handle");

		if (spr != nullptr)
		{
			UI::SetFontScale(D_SCALE + 2.0f);
			if (UI::Button(m_FlipMessage, spr) || spe::Input::OnKeyRelease(spe::KeyBoardCode::F))
			{
				spe::Sprite* door = this->m_ptr_Config->ptr_Sprites->GetByName("Door");

				if (this->m_IsEneryOn && !this->m_IsDoorOpen)
				{
					door->SetSpriteTexture("Assets\\Sprites\\Enviroment\\ComputerRoom\\Door\\open_3.png");
					door->Animator.Play("open");

					this->m_IsDoorOpen = true;
				}
				else if (this->m_IsDoorOpen && this->m_IsEneryOn)
				{
					door->SetSpriteTexture("Assets\\Sprites\\Enviroment\\ComputerRoom\\Door\\Door.png");
					door->Animator.Play("close");
					this->m_IsDoorOpen = false;

				}
				else
				{
					m_FlipMessage = "!NEED_TO_ACTIVATE_ENERGY!";
				}
			}

			return;
		}
	}
    if (collided)
	{
		spe::Sprite* spr = this->m_ptr_Player->Collider.CollidedWithName("Computer_Game");

		if (spr != nullptr)
		{
			UI::SetFontScale(D_SCALE + 2.0f);
			if (UI::Button("[P] Play to obtain energy crystal", spr) || spe::Input::OnKeyRelease(spe::KeyBoardCode::P))
			{
				OnSceneChange("compiuter_game");
			}

			return;
		}
	}
	if (collided)
	{
		spe::Sprite* spr = this->m_ptr_Player->Collider.CollidedWithName("power_place");

		if (spr != nullptr)
		{
			UI::SetFontScale(D_SCALE + 2.0f);
			if (UI::Button("[P] Place power crystal", spr) || spe::Input::OnKeyRelease(spe::KeyBoardCode::P))
			{
				this->SetPowerCrystal();
			}

			return;
		}
	}
}

void ComputerRoom::SetPowerCrystal()
{
	if (!Globals::s_IsPowerEnabled)
	{
		this->m_ptr_Server->SetSpriteTexture("Assets/Sprites/Enviroment/ComputerRoom/Server_p.png");
		this->m_ptr_Server->Particles.Play();
		this->m_ptr_Server->Audio.GetAudioByName("GeneratorBoot")->Play();
		this->m_IsEneryOn = true;
	}
}
