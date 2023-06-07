#pragma once
#include "Command.h"
#include "Singleton.h"
#include <map>

namespace dae
{
	const unsigned int MAX_KEYCODES = 512;

	enum class ControllerButton : unsigned int
	{
		DPadUp = 0x0001,
		DPadDown = 0x0002,
		DPadLeft = 0x0004,
		DPadRight = 0x0008,
		Start = 0x0010,
		Back = 0x0020,
		LeftThumb = 0x0040,
		RightThumb = 0x0080,
		LeftShoulder = 0x0100,
		RightShoulder = 0x0200,
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000
	};

	enum class PressType : unsigned int
	{
		DOWN,
		UP,
		HELD
	};

	using ControllerButtonAndPressType = std::pair<ControllerButton, PressType>;
	struct ControllerButtonAndPressTypeCompare
	{
		bool operator()(const ControllerButtonAndPressType& a, const ControllerButtonAndPressType& b) const
		{
			if (a.first < b.first) return true;
			else if (a.first == b.first) return a.second < b.second;

			return false;
		}
	};

	using KeyboardButtonAndPressType = std::pair<unsigned int, PressType>;
	struct KeyboardButtonAndPressTypeCompare
	{
		bool operator()(const KeyboardButtonAndPressType& a, const KeyboardButtonAndPressType& b) const
		{
			if (a.first < b.first) return true;
			else if (a.first == b.first) return a.second < b.second;

			return false;
		}
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();

		bool ProcessInput(unsigned int sceneId);

		void AddControllerCommand(unsigned int sceneId, int controllerId, ControllerButton controllerButton, PressType pressType, Command* pCommand);
		void AddKeyboardCommand(unsigned int sceneId, unsigned int keyboardButton, PressType pressType, Command* pCommand);
		~InputManager() override;

		//void ClearAllCommands();

	private:
		class ControllersImpl;
		ControllersImpl* pControllerImpl;

		class KeyboardImpl;
		KeyboardImpl* pKeyboardImpl;
	};
}