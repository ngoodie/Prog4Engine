#include "PlayerComponent.h"
#include "GameObject.h"
#include "AnimatedTextureComponent.h"

dae::PlayerComponent::~PlayerComponent()
{

}

void dae::PlayerComponent::Initialize()
{
	GameObject* pGameObject = GetGameObject();
	pGameObject->SetPosition(m_StartX, m_StartY);

	m_pPlayerAnimTexComp = pGameObject->AddComponent(new AnimatedTextureComponent("player1.png", 64, 64, 8, 5));
	m_pPlayerAnimTexComp->SetSpritesPerSecond(1);
	m_pPlayerAnimTexComp->Play(0, 0);
}

void dae::PlayerComponent::Update(float)
{

}

void dae::PlayerComponent::FixedUpdate(float)
{

}