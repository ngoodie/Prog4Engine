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
		virtual void Render() const;

		void AddComponent(Component* pComp);

		template <typename T>
		T* GetComponent();

		template <typename T>
		bool RemoveComponent();

		void SetPosition(float x, float y);
		glm::vec3 GetPosition() const;

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_transform{};
		std::vector<Component*> m_pComponents;
	};

	template<typename T>
	inline T* GameObject::GetComponent()
	{
		//const type_info& typeInfo = typeid(T);
		auto it = std::find_if(m_pComponents.begin(), m_pComponents.end(), [](Component* pComp)
			{
				return dynamic_cast<T*>(pComp) != nullptr; //return typeid(*pComp) == typeInfo;
			});

		if (it != m_pComponents.end()) return dynamic_cast<T*>(*it);

		return nullptr;
	}

	template<typename T>
	bool GameObject::RemoveComponent()
	{
		//const type_info& typeInfo = typeid(T);
		auto it = std::find_if(m_pComponents.begin(), m_pComponents.end(), [](Component* pComp)
			{
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