#pragma once
#include <string>
#include <functional>

namespace dae
{
	class DuvelEngine
	{
	public:
		explicit DuvelEngine(const std::string& dataPath);
		~DuvelEngine();
		void Run(const std::function<void()>& load);

		DuvelEngine(const DuvelEngine& other) = delete;
		DuvelEngine(DuvelEngine&& other) = delete;
		DuvelEngine& operator=(const DuvelEngine& other) = delete;
		DuvelEngine& operator=(DuvelEngine&& other) = delete;

	private:
		const float m_FixedTimeStep = 1 / 60.f;
		const float m_TargetFps{ 120.f };
	};
}