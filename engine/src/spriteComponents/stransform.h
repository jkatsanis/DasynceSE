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

		/// <summary>
		/// Sets the texture size
		/// </summary>
		/// <param name="scale">The scale for the new textureSize</param>
		void setTextureSize(const s2d::Vector2& scale);
		void init() override;
		void pushSetup();
		void pushSpriteFromCollider(s2d::BoxColliderPositionData::Position p, bool smaller, float& tXY, float& lXY, float& nXY);
	public:
		s2d::Vector2 position;
		s2d::Vector2 texture_size;
		s2d::Vector2 next_pos;
		s2d::Vector2 last_pos;
		s2d::Vector2 position_to_parent;
		s2d::Sprite* m_attached_sprite;

		bool position_changed;

		Transform();
		Transform(s2d::Sprite* attachedSprite);
		Transform(s2d::Sprite* attachedSprite, s2d::Transform& transform);

		/// <summary>
		/// Sets the rotation
		/// </summary>
		void setRotation(uint32_t angle);

		/// <summary>
		/// This method sets the last position of the transform. Needs to be user called.
		/// Sets "positionChanged" to true if it did that succesfully. Needs to be called after the position changed (!)
		/// </summary>
		void setLastPosition();

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

