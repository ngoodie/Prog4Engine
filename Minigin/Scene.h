#pragma once
#include "SceneManager.h"
//#include "InputManager.h"
#include <map>

namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		unsigned int GetId() const { return m_Id; }
		std::string GetName() const { return m_Name; }

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		/*
		void AddControllerCommand(int controllerId, ControllerButton controllerButton, PressType pressType, Command* pCommand)
		{
			ControllerButtonAndPressType buttonAndType;
			buttonAndType.first = controllerButton;
			buttonAndType.second = pressType;

			m_ControllerCommands[controllerId][buttonAndType] = pCommand;
		}

		void AddKeyboardCommand(unsigned int keyboardButton, PressType pressType, Command* pCommand)
		{
			KeyboardButtonAndPressType keyAndType;
			keyAndType.first = keyboardButton;
			keyAndType.second = pressType;

			m_KeyboardCommands[keyAndType] = pCommand;
		}
		*/

	private: 
		explicit Scene(const std::string& name);

		static unsigned int m_Count;

		std::string m_Name;
		unsigned int m_Id;

		std::vector <std::shared_ptr<GameObject>> m_pGameObjects{};

		//std::map<KeyboardButtonAndPressType, Command*, KeyboardButtonAndPressTypeCompare> m_KeyboardCommands;
		//std::map<ControllerButtonAndPressType, Command*, KeyboardButtonAndPressTypeCompare> m_ControllerCommands[4];
	};
}