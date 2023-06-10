#include "GameCommands.h"
#include "GameObject.h"
#include "MainMenuComponent.h"

#include "SceneManager.h"

void dae::MM_Confirm::Execute()
{
	GameObject* pMainMenuGo = GetGameObject();
	auto pMainMenuComp = pMainMenuGo->GetComponent<MainMenuComponent>();

	switch (pMainMenuComp->GetState())
	{
	case MainMenuState::LOGO:
		pMainMenuComp->SetState(MainMenuState::GAME_MODE_SELECTION);
		break;
	case MainMenuState::GAME_MODE_SELECTION:
		pMainMenuComp->StartGameMode();
		break;
	default:
		break;
	}
}

void dae::MM_Select::Execute()
{
	GameObject* pMainMenuGo = GetGameObject();
	auto pMainMenuComp = pMainMenuGo->GetComponent<MainMenuComponent>();

	if (pMainMenuComp->GetState() != MainMenuState::GAME_MODE_SELECTION)
		return;

	pMainMenuComp->ChangeSelection(m_SelectionChange);
}

void dae::MM_Back::Execute()
{
	GameObject* pMainMenuGo = GetGameObject();
	auto pMainMenuComp = pMainMenuGo->GetComponent<MainMenuComponent>();

	if (pMainMenuComp->GetState() != MainMenuState::GAME_MODE_SELECTION)
		return;

	pMainMenuComp->SetState(MainMenuState::LOGO);
}

void dae::TestCommand::Execute()
{
	SceneManager::GetInstance().SetScene("Intro", true);
}