#include "cameraController.h"

void CameraController::start(const s2d::Sprite* ptr_player)
{
	this->m_ptr_player = ptr_player;
	this->m_ptr_cam = &s2d::GameObject::camera;

	this->m_ptr_cam->setZoom(this->m_ptr_cam->getZoom() * 0.70f);
}


void CameraController::update()
{
    s2d::Vector2 position = this->m_ptr_player->transform.getPosition();
	position.y += 100;
	this->m_ptr_cam->transform.setPosition(position);
}
