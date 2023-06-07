#include <SDL.h>
#include "InputManager.h"
#include <iostream>

bool dae::InputManager::ProcessInput()
{
	for (int i = 0; i < m_NrMaxControllers; ++i)
	{
		m_PreviousControllerState[i] = m_ControllerState[i];
		XInputGetState(i, &m_ControllerState[i]);
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		// etc...
	}

	for (int i = 0; i < m_NrMaxControllers; ++i)
	{
		for (const auto& pair : m_ControllerCommands[i])
		{
			if (IsButtonDown(i, WORD(pair.first)))
			{
				pair.second->Execute();
			}
		}
	}

	return true;
}

dae::InputManager::~InputManager()
{
	for (int i = 0; i < m_NrMaxControllers; ++i)
	{
		for (auto& pair : m_ControllerCommands[i])
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}
}

bool dae::InputManager::IsButtonDown(int controllerId, WORD button)
{
	return IsButtonPressed(controllerId, button) && ((m_PreviousControllerState[controllerId].Gamepad.wButtons & button) == 0);
}

bool dae::InputManager::IsButtonUp(int controllerId, WORD button)
{
	return !IsButtonPressed(controllerId, button) && ((m_PreviousControllerState[controllerId].Gamepad.wButtons & button) != 0);
}

bool dae::InputManager::IsButtonPressed(int controllerId, WORD button)
{
	return (m_ControllerState[controllerId].Gamepad.wButtons & button) != 0;
}

float dae::InputManager::LeftThumbstickX(int controllerId)
{
	int val = m_ControllerState[controllerId].Gamepad.sThumbLX;
	if (abs(val) < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
		return 0;
	}
	return static_cast<float>(val) / 32767.0f;
}

float dae::InputManager::LeftThumbstickY(int controllerId)
{
	int val = m_ControllerState[controllerId].Gamepad.sThumbLY;
	if (abs(val) < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
		return 0;
	}
	return static_cast<float>(val) / 32767.0f;
}

float dae::InputManager::RightThumbstickX(int controllerId)
{
	int val = m_ControllerState[controllerId].Gamepad.sThumbRX;
	if (abs(val) < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
		return 0;
	}
	return static_cast<float>(val) / 32767.0f;
}

float dae::InputManager::RightThumbstickY(int controllerId)
{
	int val = m_ControllerState[controllerId].Gamepad.sThumbRY;
	if (abs(val) < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
		return 0;
	}
	return static_cast<float>(val) / 32767.0f;
}