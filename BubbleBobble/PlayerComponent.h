#pragma once
#include "Component.h"

class ISoundSystem;
namespace dae
{
	enum class PlayerState : unsigned
	{
		IN_BUBBLE,
		IDLE,
		RUNNING,
		JUMPING,
		FALLING,
		SHOOT_BUBBLE,
		DEAD
	};

	enum class FacingDirection : unsigned
	{
		RIGHT,
		LEFT
	};

	class AnimatedTextureComponent;
	class ColliderComponent;
	class RigidbodyComponent;
	class LevelComponent;
	class PlayerComponent : public Component
	{
	public:
		PlayerComponent(float startX, float startY, int spriteId, int lives)
			: m_StartX{ startX }
			, m_StartY{ startY }
			, m_SpriteId{ spriteId }
			, m_Lives{ lives }
		{}

		~PlayerComponent();

		void ExitState();
		void EnterState();

		void SetState(PlayerState state)
		{
			m_PrevState = m_State;

			ExitState();
			m_State = state;
			EnterState();
		}

		void RegisterLevel(LevelComponent* pLevelComponent);

		void RegisterEnemyColliders(const std::vector<ColliderComponent*>& enemyColliders);

		void Initialize() override;

		void Reset();

		void Move(float dirX, float dirY);
		int GetLives() const { return m_Lives; }
		int GetSpriteId() const { return m_SpriteId; }

		void ShootBubble();

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override {};

	private:
		PlayerState m_State{ PlayerState::IDLE };
		PlayerState m_PrevState{ PlayerState::IDLE };
		AnimatedTextureComponent* m_pPlayerAnimTexComp{ nullptr };
		RigidbodyComponent* m_pRigidBodyComponent{ nullptr };

		LevelComponent* m_pLevelComponent{ nullptr };
		std::vector<ColliderComponent*> m_EnemyColliders;

		float m_DeathTimer{ 0 };
		float m_DeathDuration{ 2.75f / 2.f };
		float m_ShootTimer{ 0 };
		float m_ShootDuration{ 1 / 3.f };
		int m_Lives{};
		int m_SpriteId;

		float m_FreezeTimer{ 2.5f };

		float m_StartX;
		float m_StartY;

		float m_CurrentXSpeed{};
		float m_CurrentYSpeed{};

		const float m_MoveSpeed{ 150.f };
		const float m_MoveSpeedFalling{ 75.f };

		const float m_JumpSpeed{ 300.f };
		const float m_AirDecelerationSpeed{ 525.f };
		const float m_MaxFallSpeed{ 300.f };

		FacingDirection m_Direction{ FacingDirection::RIGHT };

		int m_SpriteOffset{ 16 };
		bool m_IsGrounded{ true };

		ISoundSystem* m_pSoundSystem{ nullptr };
	};
}