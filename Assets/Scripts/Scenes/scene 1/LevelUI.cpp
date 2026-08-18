#include "LevelUI.h"

void LevelUI::Start(spe::EngineConfig& config)
{
	this->m_ptr_Player = config.ptr_Sprites->GetByName("Player");
	this->ReadingNote = false;
	this->m_ptr_Game = &config;

	spe::Sprite* woa = config.ptr_Sprites->GetByName("Water_1");
	woa->Animator.Play("WaterFlow");

	// Spawn enemys of the first scene
	EnemyHandler& handler = EnemyHandler::GetInstance();
	
	for (size_t i = 0; i < LevelUI::s_FirstSceneEnemys.size(); i++)
	{
		EnemySpawn& spawn = LevelUI::s_FirstSceneEnemys[i];

		if (spawn.Type == EnemyType::Monkey)
		{
			handler.MonkeyBehaviourObject.Spawn(spawn.Position);
		}
		else if (spawn.Type == EnemyType::Rat)
		{
			handler.RatBehaviourObject.Spawn(spawn.Position);
		}
	}
}

void LevelUI::Update(std::function<void(const std::string&)> OnSceneChange)
{
	if (this->m_ptr_Player->Collider.Collided)
	{
		spe::Sprite* spr = this->m_ptr_Player->Collider.CollidedWithTag("Note-Main");
		if (spr != nullptr)
		{
			UI::SetFontScale(D_SCALE + 2.0f);

			if (UI::Button("Read note [E]", spr)
				||spe::Input::OnKeyRelease(spe::KeyBoardCode::E))
			{
				this->ReadingNote = true;
			}

			if (this->ReadingNote)
			{
				UI::SetFontScale(D_SCALE);

				UI::Window("##window", spe::Vector2(0, 200), spe::Vector2(200, 500));

				ImGui::Text("Thats some shit notes bruh");

				UI::End();

				if (spe::Input::OnKeyRelease(spe::KeyBoardCode::Escape))
				{
					this->ReadingNote = false;
				}
			}
		}

		spe::Sprite* spr2 = this->m_ptr_Player->Collider.CollidedWithName("Kanal_Down");
		if (spr2 != nullptr)
		{
			UI::SetFontScale(D_SCALE + 2.0f);

			if (UI::Button("Climb Down [S]", spr2)
				|| spe::Input::OnKeyRelease(spe::KeyBoardCode::S))
			{
				this->m_ptr_Player->Transform.Teleport(spe::Vector2(698.76f, -1185.32f));
			}
		}

		spe::Sprite* spr3 = this->m_ptr_Player->Collider.CollidedWithName("Up_teleport");
		if (spr3 != nullptr)
		{
			UI::SetFontScale(D_SCALE + 2.0f);

			if (UI::Button("Climb Up [W]", spr3)
				|| spe::Input::OnKeyRelease(spe::KeyBoardCode::W))
			{
				this->m_ptr_Player->Transform.Teleport(KANAL_TP_UP_POSITION);
			}
		}

		spe::Sprite* spr4 = this->m_ptr_Player->Collider.CollidedWithName("computer-teleport");
		if (spr4 != nullptr)
		{
			UI::SetFontScale(D_SCALE + 2.0f);

			if (UI::Button("Go To Computer Room [W]", spr4)
				|| spe::Input::OnKeyRelease(spe::KeyBoardCode::W))
			{
				// Change scene
				OnSceneChange("computer_room");
			}
		}
	}
}

std::vector<EnemySpawn> LevelUI::s_FirstSceneEnemys = {
	{ spe::Vector2(149.434f, -230.983f), EnemyType::Monkey },
	{ spe:: Vector2(1002.83f, -252.627f), EnemyType::Rat },
	{ spe::Vector2(1086.27f, -1506.32f), EnemyType::Monkey },
	// { spe::Vector2(40.0f, 45.0f), EnemyType::Rat }
};