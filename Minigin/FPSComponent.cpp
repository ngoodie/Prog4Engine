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

void dae::FPSComponent::Update([[maybe_unused]] float deltaTime)
{
	m_pGameObject->GetComponent<TextComponent>()->SetText("FPS: " + std::to_string(int(1.0f / deltaTime)));
}

void dae::FPSComponent::FixedUpdate([[maybe_unused]] float deltaTime)
{

}