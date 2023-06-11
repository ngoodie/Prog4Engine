#include <string>
#include "GameObject.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::TextureComponent::TextureComponent(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::Render() const
{
	const auto& pos = GetGameObject()->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}

dae::TextureComponent::~TextureComponent()
{

}

void dae::TextureComponent::Update(float)
{

}

void dae::TextureComponent::FixedUpdate(float)
{

}