#include "LevelUI.h"

void LevelUI::Start(spe::EngineConfig& config)
{
	this->m_ptr_Player = config.ptr_Sprites->GetByName("Player");
	this->ReadingNote = false;
	this->m_ptr_Game = &config;

	spe::Sprite* woa = config.ptr_Sprites->GetByName("Water_1");
	woa->Animator.Play("WaterFlow");
}

void LevelUI::Update(std::function<void(const std::string&)> OnSceneChange)
{
	if (this->m_ptr_Player->Collider.Collided)
	{
		spe::Sprite* spr = this->m_ptr_Player->Collider.CollidedWithTag("Note-Main");
		if (spr != nullptr)
		{
		   spe::Vector2 pos = spr->Transform.GetPosition();
		   pos.Y += 100;
		   UI::SetCursorCamera(pos);


		//	std::cout << spr->transform.GetPosition().y << std::endl;
			// ImGui::SetCursorPos(ImVec2(spr->transform.GetPosition().x + 960, 540));

			UI::SetFontScale(D_SCALE + 2.0f);

			if (UI::Button("Read note [E]")
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
			spe::Vector2 pos = spr2->Transform.GetPosition();
			pos.Y += 100;

			UI::SetCursorCamera(pos);
			UI::SetFontScale(D_SCALE + 2.0f);

			if (UI::Button("Climb Down [S]")
				|| spe::Input::OnKeyRelease(spe::KeyBoardCode::S))
			{
				this->m_ptr_Player->Transform.Teleport(spe::Vector2(698.76f, -1185.32f));
			}
		}

		spe::Sprite* spr3 = this->m_ptr_Player->Collider.CollidedWithName("Up_teleport");
		if (spr3 != nullptr)
		{
			spe::Vector2 pos = spr3->Transform.GetPosition();
			pos.Y += 100;

			UI::SetCursorCamera(pos);
			UI::SetFontScale(D_SCALE + 2.0f);

			if (UI::Button("Climb Up [W]")
				|| spe::Input::OnKeyRelease(spe::KeyBoardCode::W))
			{
				this->m_ptr_Player->Transform.Teleport(spe::Vector2(761.003, -393.936));
			}
		}

		spe::Sprite* spr4 = this->m_ptr_Player->Collider.CollidedWithName("computer-teleport");
		if (spr4 != nullptr)
		{
 			spe::Vector2 pos = spr4->Transform.GetPosition();
			pos.Y += 100;

			UI::SetCursorCamera(pos);
			UI::SetFontScale(D_SCALE + 2.0f);

			if (UI::Button("Climb Up [W]")
				|| spe::Input::OnKeyRelease(spe::KeyBoardCode::W))
			{
				// Change scene
				OnSceneChange("computer_room");
			}
		}
	}
}

