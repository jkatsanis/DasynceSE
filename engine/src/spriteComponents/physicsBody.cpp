#include "physicsBody.h"
#include <physicalComponents/sprite.h>

//Constructor


s2d::PhsysicsBody::PhsysicsBody()
{
    this->init();
}

s2d::PhsysicsBody::PhsysicsBody(s2d::Sprite* ptr_attachedSprite)
{
    this->init();
    this->ptr_attachedSprite = ptr_attachedSprite;
}

void s2d::PhsysicsBody::init()
{
    this->ptr_attachedSprite = nullptr;
    this->reset();
}


//Public functions

void s2d::PhsysicsBody::reset()
{
	this->exist = false;
	this->mass = 0.0f;
	this->velocity = s2d::Vector2(0.0f, 0.0f);
    this->mass = 0.0f;
	this->gravity = 0.0f;
}

void s2d::PhsysicsBody::fixedUpdate()
{
    if (!this->exist || this->ptr_attachedSprite == nullptr || this->gravity == 0) return;

	//ALl Physic calcutions will happen here! -> calle from s2d::physics::update();
    const s2d::Vector2 dir = this->velocity * s2d::Time::s_delta_time;
    this->ptr_attachedSprite->transform.position += dir;

    if (this->exist)
    {
        if (this->ptr_attachedSprite->collider.isInCollision() && this->ptr_attachedSprite->collider.position_data.isEqual(s2d::BoxColliderPositionData::Down))
        {
            this->velocity.y = 0.0f;
        }
        else
        {
            this->velocity.y -= this->gravity * s2d::Time::s_delta_time;
        }
    }
}

