#pragma once
#include "SceneManager.h"
#include <map>
#include <functional>

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
		void LateUpdate(float deltaTime);
		void Render() const;

		unsigned int GetId() const { return m_Id; }
		std::string GetName() const { return m_Name; }

		void SetRestartFunction(std::function<void()> restartFunction)
		{
			m_RestartFunction = restartFunction;
		}

		void Restart()
		{
			m_RestartFunction();
		}

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		static unsigned int m_Count;

		std::string m_Name;
		unsigned int m_Id;

		std::vector <std::shared_ptr<GameObject>> m_pGameObjects{};

		std::function<void()> m_RestartFunction;
	};
}