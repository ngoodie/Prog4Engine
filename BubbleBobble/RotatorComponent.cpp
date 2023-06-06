#include <string>
#include "RotatorComponent.h"

#include "GameObject.h"
#include <iostream>

dae::RotatorComponent::RotatorComponent(float radius, float speed, bool clockWise)
	: m_Radius { radius}
	, m_Speed { speed }
{
	if (clockWise)
	{
		m_Direction = 1.f;
	}
	else
	{
		m_Direction = -1.f;
	}
}

dae::RotatorComponent::~RotatorComponent()
{

}

void dae::RotatorComponent::Update(float deltaTime)
{
	m_CurrentAngle += deltaTime * m_Speed * m_Direction;
	GetGameObject()->SetPosition(m_Radius * std::cosf(m_CurrentAngle), m_Radius * std::sinf(m_CurrentAngle));
}

void dae::RotatorComponent::FixedUpdate([[maybe_unused]] float deltaTime)
{

}