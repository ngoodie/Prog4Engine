#pragma once
#include "Component.h"
#include <vector>

namespace dae
{
	class PlayerLivesComponent : public Component, public IObserver
	{
	public:
		PlayerLivesComponent(float posX, float posY);
		~PlayerLivesComponent();

		void Initialize() override;

		void SetSpriteId(int spriteId) { m_SpriteId = spriteId; }
		void InitializeLives(int lives);

		void ReceiveNotification(unsigned eventId, Component* pComponent) override;

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override {};

	private:
		std::vector<GameObject*> m_pLivesGameObjects{ nullptr };
		int m_Lives{ -1 };

		int m_SpriteId{ 1 };

		float m_PosX;
		float m_PosY;
	};
}