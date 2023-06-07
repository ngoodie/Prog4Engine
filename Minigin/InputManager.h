#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#include <SDL.h>
#include "Command.h"
#include "Singleton.h"
#include <map>

namespace dae
{
	enum class ContollerButton : WORD
	{
		DPadUp	= 0x0001,
		DPadDown = 0x0002,
		DPadLeft = 0x0004,
		DPadRight =	0x0008,
		Start =	0x0010,
		Back = 0x0020,
		LeftThumb =	0x0040,
		RightThumb = 0x0080,
		LeftShoulder = 0x0100,
		RightShoulder =	0x0200,
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		~InputManager() override;

		bool IsButtonDown(int controllerId, WORD button);
		bool IsButtonUp(int controllerId, WORD button);
		bool IsButtonPressed(int controllerId, WORD button);

		float LeftThumbstickX(int controllerId);
		float LeftThumbstickY(int controllerId);
		float RightThumbstickX(int controllerId);
		float RightThumbstickY(int controllerId);

		void AddControllerCommand(int controllerId, dae::ContollerButton controllerButton, Command* pCommand)
		{
			m_ControllerCommands[controllerId][controllerButton] = pCommand;
		}

		//void ClearAllCommands();

	private:
		const int m_NrMaxControllers{ 4 };

		XINPUT_STATE m_ControllerState[4];
		XINPUT_STATE m_PreviousControllerState[4];

		std::map<dae::ContollerButton, Command*> m_ControllerCommands[4];

		const float m_DeadZone = 0.2f;
	};
}