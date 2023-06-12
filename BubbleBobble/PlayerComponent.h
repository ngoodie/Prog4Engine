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
	class RigidbodyComponent;
	class LevelComponent;
	class PlayerComponent : public Component
	{
	public:
		PlayerComponent(float startX, float startY, int spriteId)
			: m_StartX{ startX }
			, m_StartY{ startY }
			, m_SpriteId{ spriteId }
		{}

		~PlayerComponent();

		void ExitState();
		void EnterState();

		void SetState(PlayerState state)
		{
			ExitState();
			m_State = state;
			EnterState();
		}

		void RegisterLevel(LevelComponent* pLevelComponent);

		void Initialize() override;

		void Move(float dirX, float dirY);
		int GetLives() const { return m_Lives; }
		int GetSpriteId() const { return m_SpriteId; }

		void ShootBubble();

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override {};

	private:
		PlayerState m_State{ PlayerState::IDLE };
		AnimatedTextureComponent* m_pPlayerAnimTexComp{ nullptr };
		RigidbodyComponent* m_pRigidBodyComponent{ nullptr };

		LevelComponent* m_pLevelComponent{ nullptr };

		float m_DeathTimer{ 0 };
		float m_DeathDuration{ 2.75f / 2.f };
		float m_ShootTimer{ 0 };
		float m_ShootDuration{ 1 / 3.f };
		int m_Lives{ 3 };
		int m_SpriteId;

		float m_StartX;
		float m_StartY;

		float m_CurrentXSpeed{};
		float m_CurrentYSpeed{};

		const float m_MoveSpeed{ 150.f };
		const float m_MoveSpeedFalling{ 30.f };

		const float m_JumpSpeed{ 300.f };
		const float m_AirDecelerationSpeed{ 525.f };
		const float m_MaxFallSpeed{ 300.f };

		FacingDirection m_Direction{ FacingDirection::RIGHT };

		int m_SpriteOffset{ 16 };
		bool m_IsGrounded{ true };

		ISoundSystem* m_pSoundSystem{ nullptr };
	};
}