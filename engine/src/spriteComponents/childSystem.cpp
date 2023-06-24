#include "spriteComponents/childSystem.h"
#include <physicalComponents/sprite.h>

void s2d::ChildSystem::updatePositionToParent(s2d::Sprite* child)
{
	if (child->parent != nullptr)
	{
		s2d::Vector2 distance = s2d::Vector2(child->parent->transform.getPosition() - child->transform.getPosition());
		child->transform.position_to_parent = distance;
	}
}

void s2d::ChildSystem::updateChildPositionRecursivly(s2d::Sprite* parent)
{
	for (s2d::Sprite* child : parent->ptr_childs)
	{
		s2d::Vector2 p = parent->transform.getPosition() - child->transform.position_to_parent;
		child->transform.setPosition(p);
		s2d::Vector2 distance = s2d::Vector2(parent->transform.getPosition() - child->transform.getPosition());
		child->transform.position_to_parent = distance;

		updateChildPositionRecursivly(child);
	}
}

// RESET POSITION WHEN TREE MEMBER IS COLLIDING

void s2d::ChildSystem::updatePositionRevursivWhenChildIsColliding(s2d::Sprite* child)
{
	//Iterating over all sprites so set the position enum
	for (s2d::Sprite* node : child->ptr_childs)
	{
		setBoxColliderPosition(node, child);
		updatePositionRevursivWhenChildIsColliding(node);
	}
}


void s2d::ChildSystem::resetPositionWhenChildIsColliding(s2d::Sprite* child)
{
	if (!child->collider.collided)
	{
		return;
	}
	s2d::Sprite* node = child->getNode();

	setBoxColliderPosition(child, node);

	s2d::ChildSystem::updatePositionRevursivWhenChildIsColliding(node);
}


void s2d::ChildSystem::setBoxColliderPosition(s2d::Sprite* child, s2d::Sprite* node)
{
	child->collider.left = node->collider.left;
	child->collider.right = node->collider.right;
	child->collider.up = node->collider.up;
	child->collider.down = node->collider.down;
}
