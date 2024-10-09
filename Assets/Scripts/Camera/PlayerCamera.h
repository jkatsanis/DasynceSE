#pragma once

// Included from the editor-src
#include <Source/SpriteEngine.h>

class PlayerCamera : public spe::IScript
{

private:
	spe::Camera* m_ptr_Camera;
	const spe::Sprite* m_ptr_Player;	
	float m_Timer;

public:
	PlayerCamera() = default;

    // Can get called on start by the game/sub class
    void Start(spe::Camera* ptr, const spe::Sprite* pl);

    // Can get called 1 time per frame by the game/sub class
    void Update();

    spe::Camera* GetCamera() const { return m_ptr_Camera; }

};
