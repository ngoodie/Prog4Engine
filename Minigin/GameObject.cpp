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

void dae::GameObject::Update([[maybe_unused]]float deltaTime)
{
	for (auto& pComp : m_pComponents)
	{
		pComp->Update(deltaTime);
	}
}

void dae::GameObject::FixedUpdate([[maybe_unused]]float deltaTime)
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
	pComp->m_pGameObject = this;
	m_pComponents.push_back(pComp);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

glm::vec3 dae::GameObject::GetPosition() const
{
	return m_transform.GetPosition();
}