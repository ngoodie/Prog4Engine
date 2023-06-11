#pragma once
#include "Component.h"
#include <string>

namespace dae
{
	class TimedSceneSwitchComponent : public Component
	{
	public:
		TimedSceneSwitchComponent(float duration, std::string sceneName, bool restartScene = false)
			: m_Duration {duration}
			, m_SceneName{ sceneName }
			, m_RestartScene{ restartScene }
		{}

		~TimedSceneSwitchComponent();

		void ResetTimer() { m_Timer = 0; }

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override {};

	private:
		float m_Duration;
		std::string m_SceneName;
		bool m_RestartScene;

		float m_Timer{};
	};
}