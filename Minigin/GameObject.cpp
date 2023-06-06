#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject()
{
	for (auto& pComp : m_pComponents)
	{
		delete pComp;
		pComp = nullptr;
	}
};

void dae::GameObject::Update(float deltaTime)
{
	for (auto& pComp : m_pComponents)
	{
		pComp->Update(deltaTime);
	}
}

void dae::GameObject::FixedUpdate(float deltaTime)
{
	for (auto& pComp : m_pComponents)
	{
		pComp->FixedUpdate(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (auto& pComp : m_pComponents)
	{
		pComp->Render();
	}
}

void dae::GameObject::AddComponent(Component* pComp)
{
	pComp->InitializeGameObject(this);
	m_pComponents.push_back(pComp);
}

void dae::GameObject::SetParent(GameObject* pParent)
{
	if (m_pParent != nullptr)
	{
		m_pParent->RemoveChild(this);
	}

	m_pParent = pParent;
	//m_pParent->AddChild(this);

	//Update pos/rot/scale
}

void dae::GameObject::AddChild(GameObject* pChild)
{
	if (pChild->GetParent() != nullptr)
	{
		pChild->GetParent()->RemoveChild(pChild);
	}

	pChild->SetParent(this);
	m_pChildren.push_back(pChild);

	//Update pos/rot/scale
}

bool dae::GameObject::RemoveChild(GameObject* pChild)
{
	auto it = std::find_if(m_pChildren.begin(), m_pChildren.end(), [&pChild](GameObject* pCurrentChild)
		{
			return pChild == pCurrentChild;
		});

	if (it != m_pChildren.end())
	{
		pChild->SetParent(nullptr);
		m_pChildren.erase(it);

		//Update pos/rot/scale

		return true;
	}

	return false;
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

glm::vec3 dae::GameObject::GetPosition() const
{
	return m_transform.GetPosition();
}

glm::vec3 dae::GameObject::GetWorldPosition() const
{
	if (m_pParent != nullptr)
	{
		return m_pParent->GetWorldPosition() + GetPosition();
	}
	return GetPosition();
}