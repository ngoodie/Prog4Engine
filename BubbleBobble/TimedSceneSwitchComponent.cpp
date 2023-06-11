#include "TimedSceneSwitchComponent.h"
#include "SceneManager.h"

dae::TimedSceneSwitchComponent::~TimedSceneSwitchComponent()
{

}

void dae::TimedSceneSwitchComponent::Update(float deltaTime)
{
	if (m_Timer < m_Duration)
	{
		m_Timer += deltaTime;
		if (m_Timer >= m_Duration)
		{
			SceneManager::GetInstance().SetScene(m_SceneName, m_RestartScene);
		}
	}
}

void dae::TimedSceneSwitchComponent::FixedUpdate(float)
{

}