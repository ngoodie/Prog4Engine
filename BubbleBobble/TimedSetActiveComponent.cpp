#include "TimedSetActiveComponent.h"
#include "GameObject.h"

dae::TimedSetActiveComponent::~TimedSetActiveComponent()
{

}

void dae::TimedSetActiveComponent::Update(float deltaTime)
{
	if (m_Timer < m_Duration)
	{
		m_Timer += deltaTime;
		if (m_Timer >= m_Duration)
		{
			GetGameObject()->SetActive(m_IsActive);
		}
	}
}

void dae::TimedSetActiveComponent::FixedUpdate(float)
{

}