#include <string>
#include "GameObject.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::TextureComponent::TextureComponent(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::Render() const
{
	const auto& pos = GetGameObject()->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

dae::TextureComponent::~TextureComponent()
{

}

void dae::TextureComponent::Update([[maybe_unused]]float deltaTime)
{

}

void dae::TextureComponent::FixedUpdate([[maybe_unused]] float deltaTime)
{

}