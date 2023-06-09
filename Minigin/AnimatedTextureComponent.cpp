#include <string>
#include "GameObject.h"
#include "AnimatedTextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <iostream>

dae::AnimatedTextureComponent::AnimatedTextureComponent(const std::string& filename, int spriteWidth, int spriteHeight, int nrCols, int nrRows)
	: m_SpriteWidth{ spriteWidth }
	, m_SpriteHeight{ spriteHeight }
	, m_NrCols{ nrCols }
	, m_NrRows{ nrRows }
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

dae::AnimatedTextureComponent::~AnimatedTextureComponent()
{

}

void dae::AnimatedTextureComponent::Update(float deltaTime)
{
	if (m_Animate)
	{
		m_AnimationTimer -= deltaTime;
		if (m_AnimationTimer <= 0)
		{
			if (m_PlayReverse)
			{
				if (--m_CurSpriteId < m_StartSpriteId)
				{
					if (m_PlayBackAndForth)
					{
						m_PlayReverse = !m_PlayReverse;
						m_CurSpriteId = m_StartSpriteId + 1;
					}
					else if (m_PlayOnce)
					{
						m_CurSpriteId = m_StartSpriteId;
						m_Animate = false;
						return;
					}
					else
					{
						m_CurSpriteId = m_EndSpriteId;
					}
				}
			}
			else if (++m_CurSpriteId > m_EndSpriteId)
			{
				if (m_PlayBackAndForth)
				{
					m_PlayReverse = !m_PlayReverse;
					m_CurSpriteId = m_EndSpriteId - 1;
				}
				else if (m_PlayOnce)
				{
					m_CurSpriteId = m_EndSpriteId;
					m_Animate = false;
					return;
				}
				else
				{
					m_CurSpriteId = m_StartSpriteId;
				}
			}

			m_AnimationTimer = m_SpritesPerSecond;
		}
	}
}

void dae::AnimatedTextureComponent::Render() const
{
	const auto& pos = GetGameObject()->GetWorldPosition();

	int srcX = m_CurSpriteId % (m_NrCols);
	int srcY = m_CurSpriteId / (m_NrCols);

	//std::cout << "srcX = " << srcX << ", srcY = " << srcY << std::endl;

	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, m_SpriteWidth, m_SpriteHeight, srcX * m_SpriteWidth, srcY * m_SpriteHeight);
}

void dae::AnimatedTextureComponent::SetSpritesPerSecond(int spritesPerSecond)
{
	m_SpritesPerSecond = 1.f / spritesPerSecond;
}

void dae::AnimatedTextureComponent::Play(int startSpriteId, int endSpriteId, bool playOnce, bool playBackAndForth)
{
	m_StartSpriteId = startSpriteId;
	m_EndSpriteId = endSpriteId;
	m_PlayOnce = playOnce;
	m_PlayBackAndForth = playBackAndForth;

	m_CurSpriteId = startSpriteId;
	m_AnimationTimer = m_SpritesPerSecond;

	m_Animate = true;
}

void dae::AnimatedTextureComponent::FixedUpdate([[maybe_unused]] float deltaTime)
{

}