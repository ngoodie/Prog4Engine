#pragma once
#include "Component.h"
#include "Texture2D.h"
#include <string>

namespace dae
{
	class AnimatedTextureComponent : public Component
	{
	public:
		AnimatedTextureComponent(const std::string& filename, int spriteWidth, int spriteHeight, int nrCols, int nrRows);
		~AnimatedTextureComponent() override;

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override;

		void SetSpritesPerSecond(int spritesPerSecond);

		void Play(int startSpriteId, int endSpriteId, bool playOnce = false, bool playBackAndForth = false);

		int GetSpriteWidth() const { return m_SpriteWidth; }
		int GetSpriteHeight() const { return m_SpriteHeight; }

		AnimatedTextureComponent(const AnimatedTextureComponent& other) = delete;
		AnimatedTextureComponent(AnimatedTextureComponent&& other) = delete;
		AnimatedTextureComponent& operator=(const AnimatedTextureComponent& other) = delete;
		AnimatedTextureComponent& operator=(AnimatedTextureComponent&& other) = delete;

	private:
		std::shared_ptr<Texture2D> m_pTexture{};

		int m_SpriteWidth;
		int m_SpriteHeight;

		int m_NrRows;
		int m_NrCols;

		int m_CurSpriteId{};

		int m_StartSpriteId{};
		int m_EndSpriteId{};

		float m_AnimationTimer{};
		float m_SpritesPerSecond{ 1.f / 4 };

		bool m_Animate{ false };
		bool m_PlayOnce{ false };
		bool m_PlayBackAndForth{ false };
		bool m_PlayReverse{ false };
	};
}