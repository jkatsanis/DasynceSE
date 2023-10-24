#pragma once

#include <calculationComponents/vector2.h>
#include <spriteComponents/childSystem.h>
#include <spriteComponents/boxCollider.h>
#include <spriteComponents/component.h>

namespace s2d
{
	class Sprite;
	class Transform : private s2d::Component
	{
	private:
		s2d::Vector2 m_scale;
		uint32_t m_rotation;
		s2d::Vector2 m_position;
		s2d::Sprite* m_attached_sprite;

		/// <summary>
		/// Sets the texture size
		/// </summary>
		/// <param name="scale">The scale for the new textureSize</param>
		void setTextureSize(const s2d::Vector2& scale);
		void init() override;
		s2d::Vector2 validatePositionInput(const s2d::Vector2& position);
		void updateSpritePositionToParent(const s2d::Vector2& position);
	public:
		s2d::Vector2 texture_size;
		s2d::Vector2 position_to_parent;

		bool position_changed;

		Transform();
		Transform(s2d::Sprite* attachedSprite);
		Transform(s2d::Sprite* attachedSprite, s2d::Transform& transform);

		void addPositionX(const float x);
		void setPosition(const s2d::Vector2& positon);
		void setPositionForce(const s2d::Vector2& positon) { this->m_position = positon; }

		s2d::Vector2 getPosition() { return this->m_position; }

		/// <summary>
		/// Sets the rotation
		/// </summary>
		void setRotation(uint32_t angle);

		/// <summary>
		/// DO NOT USE
		/// </summary>
		void updateTransformPosition();

		/// <summary>
		/// Updates the origin using the �default size
		/// </summary>
		void setOrigin();

		/// <summary>
		/// Sets the new scale
		/// </summary>
		/// <param name="setScaleForce">Sets the scale even if its the same, not remommended</param>
		void setScale(const s2d::Vector2& scale, bool setScaleForce = false);
		s2d::Vector2 const getScale() { return this->m_scale; }

		uint32_t getRotation() const { return this->m_rotation; }

		s2d::Vector2 getDefaultTextureSize() const;

		void reset() override;

	public:
		//Used in poll events
		static void onPositionChange(s2d::Sprite* sprite);
	};
}

