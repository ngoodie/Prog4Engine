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

	for (auto& pChild : m_pChildren)
	{
		pChild->Update(deltaTime);
	}
}

void dae::GameObject::FixedUpdate(float deltaTime)
{
	for (auto& pComp : m_pComponents)
	{
		pComp->FixedUpdate(deltaTime);
	}

	for (auto& pChild : m_pChildren)
	{
		pChild->FixedUpdate(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (auto& pComp : m_pComponents)
	{
		pComp->Render();
	}

	for (auto& pChild : m_pChildren)
	{
		pChild->Render();
	}
}

void dae::GameObject::SetParent(GameObject* pParent)
{
	if (m_pParent != nullptr)
	{
		m_pParent->RemoveChild(this);
	}
	m_pParent = pParent;

	SetDirty(true);
}

void dae::GameObject::AddChild(std::shared_ptr<GameObject> pChild)
{
	pChild->SetParent(this);

	m_pChildren.emplace_back(std::move(pChild));
}

/*
void dae::GameObject::AddChild(GameObject* pChild)
{
	pChild->SetParent(this);

	m_pChildren.push_back(pChild);
}
*/

bool dae::GameObject::RemoveChild(GameObject* pChild)
{
	auto it = std::find_if(m_pChildren.begin(), m_pChildren.end(), [&pChild](std::shared_ptr<GameObject> pCurrentChild)	{
		return pChild == pCurrentChild.get();
	});

	if (it != m_pChildren.end())
	{
		pChild->SetParent(nullptr);
		m_pChildren.erase(it);

		return true;
	}

	return false;
}

void dae::GameObject::SetDirty(bool isDirty)
{
	m_Transform.SetDirty(isDirty);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);

	for (auto pChild : m_pChildren)
	{
		pChild->SetDirty(true);
	}
}

glm::vec3 dae::GameObject::GetPosition() const
{
	return m_Transform.GetPosition();
}

glm::vec3 dae::GameObject::GetWorldPosition()
{
	if (m_Transform.IsDirty())
	{
		m_Transform.SetDirty(false);
		if (m_pParent != nullptr)
		{
			m_Transform.SetCachedPosition(m_pParent->GetWorldPosition());
			return m_Transform.GetCachedPosition() + GetPosition();
		}
		else
		{
			return GetPosition();
		}
	}
	else //if not dirty
	{
		if (m_pParent != nullptr)
		{
			return m_Transform.GetCachedPosition() + GetPosition();
		}
		else
		{
			return GetPosition();
		}
	}
}