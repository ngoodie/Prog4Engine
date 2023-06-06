#pragma once
#include "Component.h"

namespace dae
{
	class RotatorComponent : public Component
	{
	public:
		RotatorComponent(float radius, float speed, bool clockWise);
		~RotatorComponent();

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override {};

	private:
		float m_Radius{};
		float m_Speed{};
		float m_Direction{};

		float m_CurrentAngle{};
	};
}