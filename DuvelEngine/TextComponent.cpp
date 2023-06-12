#include <string>
#include "GameObject.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

dae::TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font, uint8_t r, uint8_t g, uint8_t b)
	: m_NeedsUpdate(true)
	, m_Text(text)
	, m_Text2(text)
	, m_pFont(std::move(font))
	, m_pTextTexture(nullptr)
	, m_R{ r }
	, m_G{ g }
	, m_B{ b }
{	
	Update(0);
}

int dae::TextComponent::GetWidth() const
{
	return m_pTextTexture->GetWidth();
}

int dae::TextComponent::GetHeight() const
{
	return m_pTextTexture->GetSize().y;
}

void dae::TextComponent::SetColorOverTime(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, float duration, int updatesPerSec, bool loop)
{
	m_R1 = r1;
	m_G1 = g1;
	m_B1 = b1;
	
	m_R2 = r2;
	m_G2 = g2;
	m_B2 = b2;

	m_SetColorOverTime = true;

	m_ColorTimer = 0;
	m_ColorTimerDuration = duration;

	if (updatesPerSec != 0)
		m_UpdatesPerSec = 1.f / updatesPerSec;
	else
		m_UpdatesPerSec = 0;

	m_Loop = loop;
}

void dae::TextComponent::Update(float deltaTime)
{
	if (m_NeedsUpdate || m_SetColorOverTime)
	{
		if (m_SetColorOverTime)
		{
			bool forceUpdate{ false };

			m_ColorTimer += deltaTime;
			if (m_ColorTimer >= m_ColorTimerDuration)
			{
				forceUpdate = true;

				if (!m_Loop)
				{
					m_SetColorOverTime = false;
					m_ColorTimer = m_ColorTimerDuration;
				}
				else
				{
					m_ColorTimer -= m_ColorTimerDuration;

					m_LoopDirection = !m_LoopDirection;

					uint8_t tempR = m_R1;
					uint8_t tempG = m_G1;
					uint8_t tempB = m_B1;

					m_R1 = m_R2;
					m_G1 = m_G2;
					m_B1 = m_B2;

					m_R2 = tempR;
					m_G2 = tempG;
					m_B2 = tempB;

					if (m_LoopDirection)
					{
						std::string tempText{ m_Text };
						m_Text = m_Text2;
						m_Text2 = tempText;
					}
				}
			}

			float t{ m_ColorTimer / m_ColorTimerDuration };
			m_R = static_cast<uint8_t>(m_R1 + t * (m_R2 - m_R1));
			m_G = static_cast<uint8_t>(m_G1 + t * (m_G2 - m_G1));
			m_B = static_cast<uint8_t>(m_B1 + t * (m_B2 - m_B1));

			m_UpdateTimer += deltaTime;
			if (m_UpdateTimer < m_UpdatesPerSec)
			{
				if (!forceUpdate)
					return;
			}
			else
			{
				m_UpdateTimer -= m_UpdatesPerSec;
			}
		}

		SDL_Color color = { m_R, m_G, m_B };
		
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTextTexture = std::make_shared<Texture2D>(texture);

		if (m_RecenterOnDraw)
		{
			GetGameObject()->SetPosition(m_ScreenWidth / 2.f - GetWidth() / 2.f, GetGameObject()->GetWorldPosition().y);
		}

		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::FixedUpdate(float)
{

}

void dae::TextComponent::Render() const
{
	if (m_pTextTexture != nullptr)
	{
		const auto& pos = GetGameObject()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTextTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetSecondaryText(const std::string& text)
{
	m_Text2 = text;
}

void dae::TextComponent::RecenterOnDraw(bool recenter, float screenWidth)
{
	m_RecenterOnDraw = recenter;
	m_ScreenWidth = screenWidth;
}