#include "LevelUI.h"

void LevelUI::Start(spe::EngineConfig& config)
{
	this->m_ptr_Player = config.ptr_Sprites->GetByName("Player");
	this->ReadingNote = false;
}

void LevelUI::Update()
{
	if (this->m_ptr_Player->collider.collided)
	{
		spe::Sprite* spr = this->m_ptr_Player->collider.CollidedWithTag("Note-Main");
		if (spr != nullptr)
		{
		   spe::Vector2 pos = spr->transform.GetPosition();
		   pos.y += 100;
		   UI::SetCursorCamera(pos);


		//	std::cout << spr->transform.GetPosition().y << std::endl;
			// ImGui::SetCursorPos(ImVec2(spr->transform.GetPosition().x + 960, 540));

			UI::SetFontScale(D_SCALE + 2.0f);

			if (UI::Button("Read note [E]")
				||spe::Input::onKeyRelease(spe::KeyBoardCode::E))
			{
				this->ReadingNote = true;
			}

			if (this->ReadingNote)
			{
				UI::SetFontScale(D_SCALE);

				UI::Window("##window", spe::Vector2(0, 200), spe::Vector2(200, 500));

				ImGui::Text("Thats some shit notes bruh");

				UI::End();

				if (spe::Input::onKeyRelease(spe::KeyBoardCode::Escape))
				{
					this->ReadingNote = false;
				}
			}

		}
	}
}

