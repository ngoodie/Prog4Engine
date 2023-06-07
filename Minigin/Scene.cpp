#include "Scene.h"
#include "GameObject.h"

namespace dae
{
	unsigned int Scene::m_Count{ 0 };

	Scene::Scene(const std::string& name)
		: m_Name(name)
	{
		m_Id = m_Count++;
	}

	Scene::~Scene() = default;

	void Scene::Add(std::shared_ptr<GameObject> object)
	{
		m_pGameObjects.emplace_back(std::move(object));
	}

	void Scene::Remove(std::shared_ptr<GameObject> object)
	{
		m_pGameObjects.erase(std::remove(m_pGameObjects.begin(), m_pGameObjects.end(), object), m_pGameObjects.end());
	}

	void Scene::RemoveAll()
	{
		m_pGameObjects.clear();
	}

	void Scene::Update(float deltaTime)
	{
		for(auto& pGameObject : m_pGameObjects)
		{
			pGameObject->Update(deltaTime);
		}
	}

	void Scene::FixedUpdate(float deltaTime)
	{
		for (auto& pGameObject : m_pGameObjects)
		{
			pGameObject->FixedUpdate(deltaTime);
		}
	}

	void Scene::Render() const
	{
		for (const auto& pGameObject : m_pGameObjects)
		{
			pGameObject->Render();
		}
	}
}