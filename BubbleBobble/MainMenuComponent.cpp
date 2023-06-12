#include "MainMenuComponent.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "TextComponent.h"
#include <iostream>

#include "GameState.h"

dae::MainMenuComponent::MainMenuComponent(GameObject* pLogoGo, GameObject* pGameModesContainerGo, GameObject* pSinglePlayerGo, GameObject* pCoopGo, GameObject* pVersusGo, GameObject* pSelectionArrowGo)
	: m_State { MainMenuState::LOGO }
	, m_pLogoGo{ pLogoGo }
	, m_pGameModesContainerGo{ pGameModesContainerGo }
	, m_pSinglePlayerGo{ pSinglePlayerGo }
	, m_pCoopGo{ pCoopGo }
	, m_pVersusGo{ pVersusGo }
	, m_pSelectionArrowGo{ pSelectionArrowGo }
{
	
}

dae::MainMenuComponent::~MainMenuComponent()
{

}

void dae::MainMenuComponent::ExitState()
{
	switch (m_State)
	{
	case MainMenuState::LOGO:
		m_pLogoGo->SetActive(false);
		break;
	case MainMenuState::GAME_MODE_SELECTION:
		m_pGameModesContainerGo->SetActive(false);
		break;
	default:
		break;
	}
}

void dae::MainMenuComponent::EnterState()
{
	switch (m_State)
	{
	case MainMenuState::LOGO:
		m_pLogoGo->SetActive(true);
		break;
	case MainMenuState::GAME_MODE_SELECTION:
		m_pGameModesContainerGo->SetActive(true);
		break;
	default:
		break;
	}
}

void dae::MainMenuComponent::SetSelection(int selection)
{
	m_Selection = selection;
	UpdateUI();
}

void dae::MainMenuComponent::ChangeSelection(int selectionChange)
{
	m_Selection += selectionChange;

	if (m_Selection < 0)
	{
		m_Selection = 2;
	}
	else if (m_Selection > 2)
	{
		m_Selection = 0;
	}

	UpdateUI();
}

void dae::MainMenuComponent::UpdateUI()
{
	switch (m_Selection)
	{
	case 0:
		m_pSinglePlayerGo->GetComponent<TextComponent>()->SetColor(255, 255, 255);
		m_pCoopGo->GetComponent<TextComponent>()->SetColor(128, 128, 128);
		m_pVersusGo->GetComponent<TextComponent>()->SetColor(128, 128, 128);

		m_pSelectionArrowGo->SetPosition(m_pSinglePlayerGo->GetWorldPosition().x - 24.f, m_pSinglePlayerGo->GetWorldPosition().y + 2);
		break;
	case 1:
		m_pSinglePlayerGo->GetComponent<TextComponent>()->SetColor(128, 128, 128);
		m_pCoopGo->GetComponent<TextComponent>()->SetColor(255, 255, 255);
		m_pVersusGo->GetComponent<TextComponent>()->SetColor(128, 128, 128);

		m_pSelectionArrowGo->SetPosition(m_pCoopGo->GetWorldPosition().x - 24.f, m_pCoopGo->GetWorldPosition().y + 2);
		break;
	case 2:
		m_pSinglePlayerGo->GetComponent<TextComponent>()->SetColor(128, 128, 128);
		m_pCoopGo->GetComponent<TextComponent>()->SetColor(128, 128, 128);
		m_pVersusGo->GetComponent<TextComponent>()->SetColor(255, 255, 255);

		m_pSelectionArrowGo->SetPosition(m_pVersusGo->GetWorldPosition().x - 24.f, m_pVersusGo->GetWorldPosition().y + 2);
		break;
	default:
		break;
	}
}

void dae::MainMenuComponent::StartGameMode()
{
	switch (m_Selection)
	{
	case 0:
		GameState::GetInstance().SetGameMode(GameMode::SINGLEPLAYER);
		SceneManager::GetInstance().SetScene("Intro", true);
		break;
	case 1:
		GameState::GetInstance().SetGameMode(GameMode::COOP);
		SceneManager::GetInstance().SetScene("Intro", true);
		break;
	case 2:
		//SceneManager::GetInstance().SetScene("Intro", true);
		break;
	default:
		break;
	}
}

void dae::MainMenuComponent::Update(float )
{

}

void dae::MainMenuComponent::FixedUpdate(float )
{

}