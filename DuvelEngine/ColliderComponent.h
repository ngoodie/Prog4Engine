#pragma once
#include "Component.h"

namespace dae
{
	struct ColliderData
	{
		int width;
		int height;
		int offsetX;
		int offsetY;
	};

	struct CollisionRect
	{
		float p0x, p0y;
		float p1x, p1y;
		float p2x, p2y;
		float p3x, p3y;
	};

	class ColliderComponent : public Component
	{
	public:
		ColliderComponent(int width, int height, bool isTrigger = false, int offsetX = 0, int offsetY = 0);
		~ColliderComponent();

		const ColliderData& GetColliderData() { return m_ColliderData; }
		CollisionRect GetCollisionRect() const;

		bool IsTrigger() { return m_IsTrigger; }

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override;

	private:
		ColliderData m_ColliderData{};
		bool m_IsTrigger;
	};
}