#include "LadderManager.h"

void LadderManager::Start(spe::EngineConfig& cnfg, const std::string& scene)
{
	this->m_LaddersOfCurrentScene.clear();
	m_ptr_Player = cnfg.ptr_Sprites->GetByName("Player");
	cnfg.ptr_Sprites->GetSpritesByTag("Ladder", this->m_LaddersOfCurrentScene);
	this->m_GoUp = "[W] Go Up";

}

spe::Sprite* LadderManager::IsSpriteCollided(const std::unordered_map<uint32_t, spe::Sprite*>& collidedSprites,
	std::vector<spe::Sprite*>& secondArray)
{
	for (auto* sprite : secondArray) {
		if (sprite && collidedSprites.find(sprite->GetId()) != collidedSprites.end()) {
			return sprite;
		}
	}
#ifdef WIN32
	return false;
#else
	return  nullptr;
#endif
}

void LadderManager::Update()
{
	spe::Sprite* coll = IsSpriteCollided(this->m_ptr_Player->Collider.CollidedSprites, this->m_LaddersOfCurrentScene);

	if (coll != nullptr)
	{
		if (this->m_ptr_Player->Animator.GetAnimationPlaying().Name != "climb")
		{
			this->m_GoUp = "[W] Go Up";
		}
		UI::SetFontScale(D_SCALE + 2.0f);

		if (UI::Button(this->m_GoUp.c_str(), coll)
			|| spe::Input::OnKeyRelease(spe::KeyBoardCode::W))
		{
			this->m_GoUp = "[C] Climb!";
			PlayerController& controller = PlayerController::GetInstance();
			controller.LadderController.StartClimb(coll);
		}

		return;
	}

}

