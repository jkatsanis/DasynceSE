#include "PlayerLadderController.h"

void PlayerLadderController::Start(spe::Sprite* player)
{
	this->m_ptr_Player = player;
	this->m_ptr_Player->Animator.Animations["climb"].AutoAnim = false;
	this->m_Timer = 0.0f;
	this->IsOnLadder = false;
}

void PlayerLadderController::Update()
{
	if (this->m_ptr_Player->Animator.GetAnimationPlaying().Name == "climb")
	{
		this->m_Timer += spe::Time::s_DeltaTime;


		bool a = (spe::Input::OnKeyHold(spe::KeyBoardCode::C));
		bool b = this->m_ptr_Player->Collider.CollidedWithTag("Floor");

		if (spe::Input::OnKeyHold(spe::KeyBoardCode::C) && this->m_Timer > LADDER_TIMER
			&& this->m_ptr_Player->Collider.CollidedWithTag("Floor"))
		{
			this->m_Timer = 0.0f;

			this->m_ptr_Player->Animator.NextFrame();
			this->m_ptr_Player->Transform.AddPositionY(LADDER_GAP);
			
			const spe::Vector2 pos = this->m_ptr_Player->Transform.GetPosition(); // update position when climbing
			spe::Audio::SetListenerPosition(pos.X, pos.Y);
		}
		if (spe::Input::OnKeyPress(spe::KeyBoardCode::W)
			|| spe::Input::OnKeyPress(spe::KeyBoardCode::A)
			|| spe::Input::OnKeyPress(spe::KeyBoardCode::S)
			|| spe::Input::OnKeyPress(spe::KeyBoardCode::D)
			|| spe::Input::OnKeyPress(spe::KeyBoardCode::Space))
		{
			this->m_ptr_Player->Physicsbody.Exist = true;
			this->m_ptr_Player->Animator.Stop("climb");
			this->m_ptr_Ladder->Tag = "Ladder";
			this->m_ptr_Ladder = nullptr;
			this->IsOnLadder = false;
		//	this->m_ptr_Player.

		}
	}

}

void PlayerLadderController::StartClimb(spe::Sprite* ladder)
{
	this->m_ptr_Player->Physicsbody.Exist = false;

	this->m_ptr_Ladder = ladder;
	this->m_ptr_Player->Animator.Play("climb");
 	this->m_ptr_Ladder->Tag = "Floor";
	this->m_ptr_Player->Animator.NextFrame();

	this->m_ptr_Player->Transform.SetPositionX(ladder->Transform.GetPosition().X);

	this->IsOnLadder = true;
}