#pragma once
#include "Component.h"
#include <string>

namespace dae
{
	class LevelComponent : public Component
	{
	public:
		LevelComponent(std::string levelPath);
		~LevelComponent();

		virtual void Initialize() override;

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override {};

	private:
		const unsigned int LEVEL_LINE_SIZE{ 32 };
		const float TILE_SIZE{ 16.f };
		std::string m_LevelPath;
	};
}