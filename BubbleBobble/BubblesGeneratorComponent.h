#pragma once
#include "Component.h"

namespace dae
{
	class BubblesGeneratorComponent : public Component
	{
	public:
		BubblesGeneratorComponent(float bubblesPerSecond, float rotationSpeed, float bubblesSpeed, int amount);
		~BubblesGeneratorComponent();

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override {};

	private:
		float m_BubblesPerSecond{};
		float m_RotationSpeed{};
		float m_BubblesSpeed{};

		float m_CurrentAngle{};

		int m_Amount{};
		int m_Count{};

		float m_Timer{};
	};
}