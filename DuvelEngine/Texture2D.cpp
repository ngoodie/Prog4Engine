#include <SDL.h>
#include "Texture2D.h"

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}

glm::ivec2 dae::Texture2D::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w, dst.h };
}

int dae::Texture2D::GetWidth() const
{
	return GetSize().x;
}

int dae::Texture2D::GetHeight() const
{
	return GetSize().y;
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_pTexture;
}

dae::Texture2D::Texture2D(SDL_Texture* pTexture)
{
	m_pTexture = pTexture;
}