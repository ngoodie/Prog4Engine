#pragma once
#include "Component.h"
#include <string>

namespace dae
{
	class ColliderComponent;
	class LevelComponent : public Component
	{
	public:
		LevelComponent(int levelId);
		~LevelComponent();

		virtual void Initialize() override;

		const std::vector<ColliderComponent*>& GetNearbyLevelTileColliders()
		{
			return m_pTilesColliders;
		}

		const std::vector<ColliderComponent*>& GetBorderColliders()
		{
			return m_pBorderColliders;
		}

		void DeleteTiles();
		
		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override {};

	private:
		const unsigned int LEVEL_LINE_SIZE{ 32 };
		const float TILE_SIZE{ 16.f };
		std::string m_LevelPath;
		int m_LevelId;

		std::vector<ColliderComponent*> m_pTilesColliders{};
		std::vector<ColliderComponent*> m_pBorderColliders{};
	};
}