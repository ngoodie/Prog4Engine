#include <string>
#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Time.h"

dae::FPSComponent::FPSComponent()
{

}

dae::FPSComponent::~FPSComponent()
{

}

void dae::FPSComponent::Update(float deltaTime)
{
	if (m_pTextComponent == nullptr)
		m_pTextComponent = GetGameObject()->GetComponent<TextComponent>();
	
	m_pTextComponent->SetText("FPS: " + std::to_string(int(1.0f / deltaTime)));
}

void dae::FPSComponent::FixedUpdate(float)
{

}