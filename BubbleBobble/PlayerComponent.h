#pragma once
#include "Component.h"

namespace dae
{
	class AnimatedTextureComponent;
	class PlayerComponent : public Component
	{
	public:
		PlayerComponent(float startX, float startY)
			: m_StartX{ startX }
			, m_StartY{ startY }
		{}

		~PlayerComponent();
		void Initialize() override;

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override {};

	private:
		AnimatedTextureComponent* m_pPlayerAnimTexComp;
		float m_StartX;
		float m_StartY;
	};
}