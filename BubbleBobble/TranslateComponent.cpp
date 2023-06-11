#include "TranslateComponent.h"

#include "GameObject.h"
#include <iostream>

dae::TranslateComponent::TranslateComponent(float x, float y, float speed)
	: m_DirX{ x }
	, m_DirY{ y }
	, m_Speed{ speed }
{

}

dae::TranslateComponent::~TranslateComponent()
{

}

void dae::TranslateComponent::Update(float deltaTime)
{
	auto pos = GetGameObject()->GetPosition();
	GetGameObject()->SetPosition(pos.x + m_DirX * m_Speed * deltaTime, pos.y + m_DirY * m_Speed * deltaTime);
}

void dae::TranslateComponent::FixedUpdate(float)
{

}