#include "InputManager.h"
#include <SDL.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#include <iostream>

class dae::InputManager::KeyboardImpl
{
public:
	~KeyboardImpl()
	{
		for (auto& pair : m_KeyboardCommands)
		{
			for (auto& pair2 : pair.second)
			{
				delete pair2.second;
				pair2.second = nullptr;
			}
		}
	}

	void AddKeyboardCommand(unsigned int sceneId, unsigned int keyboardButton, PressType pressType, Command* pCommand)
	{
		KeyboardButtonAndPressType keyAndType;
		keyAndType.first = keyboardButton;
		keyAndType.second = pressType;

		m_KeyboardCommands[sceneId][keyAndType] = pCommand;
	};

	bool IsKeyDown(unsigned int keycode)
	{
		return IsKeyPressed(keycode) && ((m_PreviousKeyState[keycode]) == 0);
	}

	bool IsKeyUp(unsigned int keycode)
	{
		return !IsKeyPressed(keycode) && ((m_PreviousKeyState[keycode]) != 0);
	}

	bool IsKeyPressed(unsigned int keycode)
	{
		return m_KeyState[keycode];
	}

	bool ProcessInput(unsigned int sceneId)
	{
		// Keyboard input
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				return false;
			}
		}

		const Uint8* keystate;
		keystate = SDL_GetKeyboardState(NULL);

		std::copy(m_KeyState, m_KeyState + SDL_NUM_SCANCODES, m_PreviousKeyState);
		std::copy(keystate, keystate + SDL_NUM_SCANCODES, m_KeyState);

		for (const auto& pair : m_KeyboardCommands[sceneId])
		{
			switch (pair.first.second)
			{
			case PressType::DOWN:
				if (IsKeyDown(pair.first.first))
				{
					pair.second->Execute();
				}
				break;
			case PressType::UP:
				if (IsKeyUp(pair.first.first))
				{
					pair.second->Execute();
				}
				break;
			case PressType::HELD:
				if (IsKeyPressed(pair.first.first))
				{
					pair.second->Execute();
				}
				break;
			}
		}

		return true;
	}

private:
	std::map<unsigned int, std::map<KeyboardButtonAndPressType, Command*, KeyboardButtonAndPressTypeCompare>> m_KeyboardCommands;

	uint8_t m_KeyState[MAX_KEYCODES] = {};
	uint8_t m_PreviousKeyState[MAX_KEYCODES] = {};
};

class dae::InputManager::ControllersImpl
{
public:
	bool ProcessInput(unsigned int sceneId)
	{
		// Controllers input
		for (int i = 0; i < m_NrMaxControllers; ++i)
		{
			m_PreviousControllerState[i] = m_ControllerState[i];
			XInputGetState(i, &m_ControllerState[i]);
		}

		for (int i = 0; i < m_NrMaxControllers; ++i)
		{
			for (const auto& pair : m_ControllerCommands[i][sceneId])
			{
				switch (pair.first.second)
				{
				case PressType::DOWN:
					if (IsButtonDown(i, WORD(pair.first.first)))
					{
						pair.second->Execute();
					}
					break;
				case PressType::UP:
					if (IsButtonUp(i, WORD(pair.first.first)))
					{
						pair.second->Execute();
					}
					break;
				case PressType::HELD:
					if (IsButtonPressed(i, WORD(pair.first.first)))
					{
						pair.second->Execute();
					}
					break;
				}
			}
		}

		return true;
	}

	~ControllersImpl()
	{
		for (int i = 0; i < m_NrMaxControllers; ++i)
		{
			for (auto& pair : m_ControllerCommands[i])
			{
				for (auto& pair2 : pair.second)
				{
					delete pair2.second;
					pair2.second = nullptr;
				}
			}
		}
	}

	bool IsButtonDown(int controllerId, WORD button)
	{
		return IsButtonPressed(controllerId, button) && ((m_PreviousControllerState[controllerId].Gamepad.wButtons & button) == 0);
	}

	bool IsButtonUp(int controllerId, WORD button)
	{
		return !IsButtonPressed(controllerId, button) && ((m_PreviousControllerState[controllerId].Gamepad.wButtons & button) != 0);
	}

	bool IsButtonPressed(int controllerId, WORD button)
	{
		return (m_ControllerState[controllerId].Gamepad.wButtons & button) != 0;
	}

	float LeftThumbstickX(int controllerId)
	{
		int val = m_ControllerState[controllerId].Gamepad.sThumbLX;
		if (abs(val) < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
			return 0;
		}
		return static_cast<float>(val) / 32767.0f;
	}

	float LeftThumbstickY(int controllerId)
	{
		int val = m_ControllerState[controllerId].Gamepad.sThumbLY;
		if (abs(val) < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
			return 0;
		}
		return static_cast<float>(val) / 32767.0f;
	}

	float RightThumbstickX(int controllerId)
	{
		int val = m_ControllerState[controllerId].Gamepad.sThumbRX;
		if (abs(val) < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
			return 0;
		}
		return static_cast<float>(val) / 32767.0f;
	}

	float RightThumbstickY(int controllerId)
	{
		int val = m_ControllerState[controllerId].Gamepad.sThumbRY;
		if (abs(val) < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
			return 0;
		}
		return static_cast<float>(val) / 32767.0f;
	}

	void AddControllerCommand(unsigned int sceneId, int controllerId, ControllerButton controllerButton, PressType pressType, Command* pCommand)
	{
		ControllerButtonAndPressType buttonAndType;
		buttonAndType.first = controllerButton;
		buttonAndType.second = pressType;

		m_ControllerCommands[controllerId][sceneId][buttonAndType] = pCommand;
	}
private:
	const int m_NrMaxControllers{ 4 };

	XINPUT_STATE m_ControllerState[4]{};
	XINPUT_STATE m_PreviousControllerState[4]{};

	std::map<unsigned int, std::map<ControllerButtonAndPressType, Command*, ControllerButtonAndPressTypeCompare>> m_ControllerCommands[4];

	const float m_DeadZone = 0.2f;
};

void dae::InputManager::AddControllerCommand(unsigned int sceneId, int controllerId, ControllerButton controllerButton, PressType pressType, Command* pCommand)
{
	pControllerImpl->AddControllerCommand(sceneId, controllerId, controllerButton, pressType, pCommand);
}

void dae::InputManager::AddKeyboardCommand(unsigned int sceneId, unsigned int keyboardButton, PressType pressType, Command* pCommand)
{
	pKeyboardImpl->AddKeyboardCommand(sceneId, keyboardButton, pressType, pCommand);
}

dae::InputManager::InputManager()
{
	pControllerImpl = new ControllersImpl();
	pKeyboardImpl = new KeyboardImpl();
}

bool dae::InputManager::ProcessInput(unsigned int sceneId)
{
	// Controller input
	pControllerImpl->ProcessInput(sceneId);

	// Keyboard input
	return pKeyboardImpl->ProcessInput(sceneId);
}

dae::InputManager::~InputManager()
{
	delete pControllerImpl;
	pControllerImpl = nullptr;

	delete pKeyboardImpl;
	pKeyboardImpl = nullptr;
}