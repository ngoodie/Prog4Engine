#pragma once
#include "Component.h"

namespace dae
{
	class TranslateComponent : public Component
	{
	public:
		TranslateComponent(float x, float y, float speed);
		~TranslateComponent();

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override {};

	private:
		float m_DirX{};
		float m_DirY{};
		float m_Speed{};
	};
}