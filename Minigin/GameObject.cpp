#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject()
{
	for (Component* component : m_pComponents)
	{
		delete component;
		component = nullptr;
	}
};

void dae::GameObject::Update([[maybe_unused]]float deltaTime)
{
	
}

void dae::GameObject::FixedUpdate([[maybe_unused]]float deltaTime)
{
	
}

void dae::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}