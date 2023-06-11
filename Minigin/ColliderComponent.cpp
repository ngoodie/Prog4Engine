#include "ColliderComponent.h"
#include "GameObject.h"
//#include "Renderer.h"
//#include <iostream>

dae::ColliderComponent::ColliderComponent(int width, int height, bool isTrigger, int offsetX, int offsetY)
	: m_ColliderData{ width, height, offsetX, offsetY }
	, m_IsTrigger{ isTrigger }
{
	
}

dae::ColliderComponent::~ColliderComponent()
{

}

void dae::ColliderComponent::Update(float)
{

}

void dae::ColliderComponent::Render() const
{
	//auto collisionRect = GetCollisionRect();
	//SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 255, 255, 255);
	//SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(), int(collisionRect.p0x), int(collisionRect.p0y), int(collisionRect.p1x), int(collisionRect.p1y));
	//SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(), int(collisionRect.p1x), int(collisionRect.p1y), int(collisionRect.p2x), int(collisionRect.p2y));
	//SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(), int(collisionRect.p2x), int(collisionRect.p2y), int(collisionRect.p3x), int(collisionRect.p3y));
	//SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(), int(collisionRect.p3x), int(collisionRect.p3y), int(collisionRect.p0x), int(collisionRect.p0y));
}

dae::CollisionRect dae::ColliderComponent::GetCollisionRect() const
{
	CollisionRect collisionRect;
	auto pos = GetGameObject()->GetWorldPosition();
	pos.x += m_ColliderData.offsetX;
	pos.y += m_ColliderData.offsetY;

	collisionRect.p0x = pos.x;
	collisionRect.p0y = pos.y;

	collisionRect.p1x = pos.x + m_ColliderData.width;
	collisionRect.p1y = pos.y;

	collisionRect.p2x = pos.x + m_ColliderData.width;
	collisionRect.p2y = pos.y + m_ColliderData.height;

	collisionRect.p3x = pos.x;
	collisionRect.p3y = pos.y + m_ColliderData.height;

	return collisionRect;
}


void dae::ColliderComponent::FixedUpdate(float)
{

}