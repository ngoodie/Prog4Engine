#pragma once
#include "Component.h"

namespace dae
{
	enum class PlayerState : unsigned
	{
		IN_BUBBLE,
		IDLE,
		RUNNING,
		JUMPING,
		FALLING,
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
		PlayerComponent(float startX, float startY)
			: m_StartX{ startX }
			, m_StartY{ startY }
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

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override {};

	private:
		PlayerState m_State{ PlayerState::IDLE };
		AnimatedTextureComponent* m_pPlayerAnimTexComp{ nullptr };
		RigidbodyComponent* m_pRigidBodyComponent{ nullptr };

		LevelComponent* m_pLevelComponent{ nullptr };

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
	};
}