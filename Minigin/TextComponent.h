#pragma once
#include "Component.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent : public Component
	{
	public:
		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetSecondaryText(const std::string& text);

		void RecenterOnDraw(bool recenter, float screenWidth = -1);

		TextComponent(const std::string& text, std::shared_ptr<Font> font, uint8_t r, uint8_t b, uint8_t g);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		int GetWidth() const;
		int GetHeight() const;

		void SetColorOverTime(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, float duration, int updatesPerSec = 0, bool loop = false);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::string m_Text2;
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_pTextTexture;

		uint8_t m_R;
		uint8_t m_G;
		uint8_t m_B;

		uint8_t m_R1;
		uint8_t m_G1;
		uint8_t m_B1;

		uint8_t m_R2;
		uint8_t m_G2;
		uint8_t m_B2;

		bool m_SetColorOverTime{ false };
		bool m_Loop{ false };

		float m_ColorTimer{ 0 };
		float m_ColorTimerDuration{ 0 };

		float m_UpdateTimer{ 0 };
		float m_UpdatesPerSec{ 0 };

		bool m_LoopDirection{ false };

		bool m_RecenterOnDraw{ false };
		float m_ScreenWidth{ -1 };
	};
}