#pragma once
#include "Component.h"

namespace dae
{
	class TimedSetActiveComponent : public Component
	{
	public:
		TimedSetActiveComponent(float duration, bool isActive)
			: m_Duration{ duration }
			, m_IsActive{ isActive }
		{}

		~TimedSetActiveComponent();

		void ResetTimer() { m_Timer = 0; }

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override {};

	private:
		float m_Duration;
		bool m_IsActive;

		float m_Timer{};
	};
}