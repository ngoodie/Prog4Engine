#include "GameCommands.h"
#include "GameObject.h"
#include "MainMenuComponent.h"
#include "PlayerComponent.h"

#include "SceneManager.h"
#include "GameState.h"

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
	int levelId = GameState::GetInstance().GetLevelId();

	levelId++;
	if (levelId >= 1 && levelId <= 3)
	{
		GameState::GetInstance().SetLevelId(levelId);
		GameMode gameMode = GameState::GetInstance().GetGameMode();

		if (gameMode == GameMode::SINGLEPLAYER)
		{
			SceneManager::GetInstance().SetScene("SinglePlayer", true);
		}
		else if (gameMode == GameMode::COOP)
		{
			SceneManager::GetInstance().SetScene("MultiPlayer", true);
		}
	}
	else
	{
		SceneManager::GetInstance().SetScene("MainMenu", true);
	}
}

dae::MovePlayerCommand::MovePlayerCommand(GameObject* pGameObject, float dirX, float dirY)
	: Command(pGameObject)
	, m_DirX{ dirX }
	, m_DirY{ dirY }
{
	m_pPlayerComponent = pGameObject->GetComponent<PlayerComponent>();
}

void dae::MovePlayerCommand::Execute()
{
	m_pPlayerComponent->Move(m_DirX, m_DirY);
}

dae::ShootBubblePlayerCommand::ShootBubblePlayerCommand(GameObject* pGameObject)
	: Command(pGameObject)
{
	m_pPlayerComponent = pGameObject->GetComponent<PlayerComponent>();
}

void dae::ShootBubblePlayerCommand::Execute()
{
	m_pPlayerComponent->ShootBubble();
}