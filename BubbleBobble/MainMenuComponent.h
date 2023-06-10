#pragma once
#include "Component.h"

namespace dae
{
	enum class MainMenuState : unsigned
	{
		LOGO,
		GAME_MODE_SELECTION
	};

	enum class MainMenuSelections : unsigned
	{
		SINGLE_PLAYER,
		COOP,
		VERSUS
	};

	class MainMenuComponent : public Component//, public IObserver
	{
	public:
		MainMenuComponent(GameObject* pLogoGo, GameObject* pGameModesContainerGo, GameObject* pSinglePlayerGo, GameObject* pCoopGo, GameObject* pVersusGo, GameObject* pSelectionArrowGo);
		~MainMenuComponent();

		void ExitState();
		void EnterState();

		void SetState(MainMenuState state)
		{
			ExitState();
			m_State = state;
			EnterState();
		}
		MainMenuState GetState() const { return m_State; }

		void ChangeSelection(int selectionChange);
		void SetSelection(int selection);
		void UpdateUI();

		void StartGameMode();

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override {};

		//virtual void ReceiveNotification(unsigned eventId, Component* pComponent) override;

	private:
		MainMenuState m_State;
		int m_Selection{ 0 };

		GameObject* m_pLogoGo;
		GameObject* m_pGameModesContainerGo;
		GameObject* m_pSinglePlayerGo;
		GameObject* m_pCoopGo;
		GameObject* m_pVersusGo;
		GameObject* m_pSelectionArrowGo;
	};
}