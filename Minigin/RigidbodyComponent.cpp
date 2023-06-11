#include "RigidbodyComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include <iostream>

dae::RigidbodyComponent::~RigidbodyComponent()
{
}

void dae::RigidbodyComponent::Initialize()
{
	m_pColliderComponent = GetGameObject()->GetComponent<ColliderComponent>();
}

bool dae::RigidbodyComponent::Move(float x, float y, const std::vector<ColliderComponent*>& pColliders)
{
	auto colliderData = m_pColliderComponent->GetColliderData();
	auto collisionRect = m_pColliderComponent->GetCollisionRect();

	auto pos = GetGameObject()->GetWorldPosition();
	float collisionX{};
	float collisionY{};

	if (x != 0)
	{
		GetGameObject()->SetPosition(pos.x + x, pos.y);
		if (IsCollidingWith(pColliders, collisionX, collisionY))
		{
			GetGameObject()->SetPosition(pos.x, pos.y);
			//if (collisionX > pos.x + x)
			//	GetGameObject()->SetPosition(collisionX - colliderData.offsetX, pos.y);
			//else if (collisionX != pos.x + x)
				//GetGameObject()->SetPosition(collisionX + colliderData.offsetX * 2 + colliderData.width , pos.y);
			//std::cout << "xCollision !" << std::endl;
		}
	}

	if (y != 0)
	{
		pos = GetGameObject()->GetWorldPosition();
		GetGameObject()->SetPosition(pos.x, pos.y + y);
		if (IsCollidingWith(pColliders, collisionX, collisionY))
		{
			GetGameObject()->SetPosition(pos.x, pos.y);
			//std::cout << "yCollision !" << std::endl;

			float minY = std::min({ collisionRect.p0y, collisionRect.p1y, collisionRect.p2y, collisionRect.p3y });
			return (minY <= collisionY);
		}
	}

	return false;
}

bool dae::RigidbodyComponent::IsCollidingWith(const std::vector<ColliderComponent*>& pColliders, float& collisionX, float& collisionY)
{
	auto collisionRect = m_pColliderComponent->GetCollisionRect();

	bool didCollide{ false };
	for (auto pCollider : pColliders)
	{
		auto otherCollisionRect = pCollider->GetCollisionRect();
		didCollide = IsPointInRect(otherCollisionRect.p0x, otherCollisionRect.p0y, collisionRect);
		collisionX = otherCollisionRect.p0x;
		collisionY = otherCollisionRect.p0y;
		if (didCollide)	break;

		didCollide = IsPointInRect(otherCollisionRect.p1x, otherCollisionRect.p1y, collisionRect);
		collisionX = otherCollisionRect.p1x;
		collisionY = otherCollisionRect.p1y;
		if (didCollide)	break;

		didCollide = IsPointInRect(otherCollisionRect.p2x, otherCollisionRect.p2y, collisionRect);
		collisionX = otherCollisionRect.p2x;
		collisionY = otherCollisionRect.p2y;
		if (didCollide)	break;

		didCollide = IsPointInRect(otherCollisionRect.p3x, otherCollisionRect.p3y, collisionRect);
		collisionX = otherCollisionRect.p3x;
		collisionY = otherCollisionRect.p3y;
		if (didCollide)	break;
	}

	return didCollide;
}

void dae::RigidbodyComponent::Update(float)
{

}

void dae::RigidbodyComponent::FixedUpdate(float)
{

}

bool dae::RigidbodyComponent::IsPointInRect(float x, float y, const CollisionRect& collisionRect)
{
	float minX = std::min({ collisionRect.p0x, collisionRect.p1x, collisionRect.p2x, collisionRect.p3x });
	float maxX = std::max({ collisionRect.p0x, collisionRect.p1x, collisionRect.p2x, collisionRect.p3x });

	float minY = std::min({ collisionRect.p0y, collisionRect.p1y, collisionRect.p2y, collisionRect.p3y });
	float maxY = std::max({ collisionRect.p0y, collisionRect.p1y, collisionRect.p2y, collisionRect.p3y });

	return (x > minX && x < maxX && y > minY && y < maxY);
}