#include "BubblesGeneratorComponent.h"

#include "GameObject.h"
#include "AnimatedTextureComponent.h"
#include "TranslateComponent.h"
//#include <iostream>

dae::BubblesGeneratorComponent::BubblesGeneratorComponent(float bubblesPerSecond, float rotationSpeed, float bubblesSpeed, int amount)
	: m_BubblesPerSecond{ bubblesPerSecond }
	, m_RotationSpeed{ rotationSpeed }
	, m_BubblesSpeed{ bubblesSpeed }
	, m_Amount{ amount }
{

}

dae::BubblesGeneratorComponent::~BubblesGeneratorComponent()
{

}

void dae::BubblesGeneratorComponent::Update(float deltaTime)
{
	if (m_Count < m_Amount)
	{
		m_CurrentAngle += deltaTime * m_RotationSpeed;

		m_Timer += deltaTime;
		if (m_Timer >= m_BubblesPerSecond)
		{
			auto pBubble = std::make_shared<GameObject>();
			auto pAnimTexComp = pBubble->AddComponent(new AnimatedTextureComponent("bubbles_intro.png", 32, 32, 6, 1));
			pAnimTexComp->SetSpritesPerSecond(5);
			pAnimTexComp->Play(0, 6, true);
			pBubble->SetPosition(-pAnimTexComp->GetSpriteWidth() / 2.f, -pAnimTexComp->GetSpriteHeight() / 2.f);
			pBubble->AddComponent(new TranslateComponent(std::cosf(m_CurrentAngle), std::sinf(m_CurrentAngle), m_BubblesSpeed));
			GetGameObject()->AddChild(pBubble);

			//pBubble->SetPosition(m_BubblesSpeed * std::cosf(m_CurrentAngle), m_BubblesSpeed * std::sinf(m_CurrentAngle));

			m_Timer = 0;
			m_Count++;
		}
	}
}

void dae::BubblesGeneratorComponent::FixedUpdate([[maybe_unused]] float deltaTime)
{

}