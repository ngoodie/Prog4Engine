#pragma once
#include "Component.h"

namespace dae
{
	class ColliderComponent;
	struct CollisionRect;
	class RigidbodyComponent : public Component
	{
	public:
		RigidbodyComponent() {};
		~RigidbodyComponent();

		void Initialize() override;
		bool Move(float x, float y, const std::vector<ColliderComponent*>& pColliders);

		bool IsCollidingWith(const std::vector<ColliderComponent*>& pColliders, float& collisionX, float& collisionY);

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override {};

	private:
		bool IsPointInRect(float x, float y, const CollisionRect& collisionRect);
		//bool IsRectInRect(const CollisionRect& collisionRect, const CollisionRect& otherCollisionRect);

		ColliderComponent* m_pColliderComponent{ nullptr };
	};
}