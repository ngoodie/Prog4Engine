#pragma once
#include <memory>
#include "Transform.h"
#include "Component.h"
#include <vector>

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float deltaTime);
		virtual void LateUpdate(float deltaTime);
		virtual void Render() const;

		template <typename T>
		T* AddComponent(T* pComp);

		template <typename T>
		T* GetComponent();

		template <typename T>
		bool RemoveComponent();

		GameObject* GetParent() const { return m_pParent; };

		void AddChild(std::shared_ptr<GameObject> pChild);
		bool RemoveChild(GameObject* pChild);

		void SetDirty(bool isDirty);
		void RemoveAllChildren();

		void SetActive(bool isActive)
		{
			m_IsActive = isActive;

			for (auto pChild : m_pChildren)
			{
				pChild->SetActive(isActive);
			}
		}

		std::vector<std::shared_ptr<GameObject>>& GetChildren() { return m_pChildren; }

		bool IsActive() { return m_IsActive; }

		void SetPosition(float x, float y);
		glm::vec3 GetPosition() const;
		glm::vec3 GetWorldPosition();

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		bool m_IsActive{ true };
		bool m_RemoveAllChildren{ false };

		Transform m_Transform{};
		std::vector<Component*> m_pComponents;

		GameObject* m_pParent = nullptr;
		std::vector<std::shared_ptr<GameObject>> m_pChildren;

		void SetParent(GameObject* pParent);
	};

	template <typename T>
	T* GameObject::AddComponent(T* pComp)
	{
		pComp->InitializeGameObject(this);
		m_pComponents.push_back(pComp);

		return pComp;
	}

	template<typename T>
	inline T* GameObject::GetComponent()
	{
		//const type_info& typeInfo = typeid(T);
		auto it = std::find_if(m_pComponents.begin(), m_pComponents.end(), [](Component* pComp)	{
			return dynamic_cast<T*>(pComp) != nullptr; //return typeid(*pComp) == typeInfo;
		});

		if (it != m_pComponents.end()) return dynamic_cast<T*>(*it);

		return nullptr;
	}

	template<typename T>
	bool GameObject::RemoveComponent()
	{
		//const type_info& typeInfo = typeid(T);
		auto it = std::find_if(m_pComponents.begin(), m_pComponents.end(), [](Component* pComp)	{
			return dynamic_cast<T*>(pComp) != nullptr; //return typeid(*pComp) == typeInfo;
		});

		if (it != m_pComponents.end())
		{
			delete *it;
			m_pComponents.erase(it);

			return true;
		}
		
		return false;
	}
}