#include "PlayerLivesComponent.h"
#include "GameObject.h"
#include <string>
#include "TextureComponent.h"
#include "PlayerComponent.h"
#include "GameEvents.h"
#include <iostream>


dae::PlayerLivesComponent::PlayerLivesComponent(float posX, float posY)
    : m_PosX{ posX }
    , m_PosY{ posY }
{

}

dae::PlayerLivesComponent::~PlayerLivesComponent()
{

}

void dae::PlayerLivesComponent::Initialize()
{
    
}

void dae::PlayerLivesComponent::InitializeLives(int lives)
{
    auto pGameObject = GetGameObject();

    m_Lives = lives;
    if (m_Lives < 0) m_Lives = 0;

    for (int i{}; i < m_Lives; i++)
    {
        auto pGo = std::make_shared<GameObject>();
        pGo->AddComponent(new TextureComponent("lives_player" + std::to_string(m_SpriteId) + ".png"));
        pGo->SetPosition(m_PosX + i * 16.f, m_PosY);
        pGameObject->AddChild(pGo);

        m_pLivesGameObjects.emplace_back(pGo.get());
    }
}

void dae::PlayerLivesComponent::ReceiveNotification(unsigned eventId, Component* pComponent)
{
    auto pPlayerComponent = dynamic_cast<PlayerComponent*>(pComponent);
    if (pPlayerComponent != nullptr)
    {
        if (PlayerEvents(eventId) == PlayerEvents::DIED)
        {
            m_pLivesGameObjects[m_Lives]->SetActive(false);

            m_Lives = pPlayerComponent->GetLives();
            if (m_Lives < 0) m_Lives = 0;
        }
    }
}

void dae::PlayerLivesComponent::Update(float)
{

}

void dae::PlayerLivesComponent::FixedUpdate(float)
{

}