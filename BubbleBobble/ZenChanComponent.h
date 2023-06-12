#pragma once
#include "Component.h"

class ISoundSystem;
namespace dae
{
	enum class ZenChanState : unsigned
	{
		RUNNING,
		RUNNING_ANGRY,
		DEAD,
		IN_BUBBLE_1,
		IN_BUBBLE_2,
		IN_BUBBLE_3,
	};

	enum class EnemyFacingDirection : unsigned
	{
		LEFT,
		RIGHT
	};

	class AnimatedTextureComponent;
	class RigidbodyComponent;
	class LevelComponent;
	class ZenChanComponent : public Component
	{
	public:
		ZenChanComponent(float startX, float startY, EnemyFacingDirection facingDirection)
			: m_StartX{ startX }
			, m_StartY{ startY }
			, m_Direction{ facingDirection }
			, m_StartDirection{ facingDirection }
		{}

		~ZenChanComponent();

		void ExitState();
		void EnterState();

		void SetState(ZenChanState state)
		{
			m_PrevState = m_State;

			ExitState();
			m_State = state;
			EnterState();
		}

		void RegisterLevel(LevelComponent* pLevelComponent);

		void Initialize() override;

		void Reset();

		void Move(float dirX, float dirY);

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override {};

	private:
		ZenChanState m_State{ ZenChanState::RUNNING };
		ZenChanState m_PrevState{ ZenChanState::RUNNING };
		AnimatedTextureComponent* m_pAnimTexComp{ nullptr };
		RigidbodyComponent* m_pRigidBodyComponent{ nullptr };

		LevelComponent* m_pLevelComponent{ nullptr };

		float m_FreezeTimer{ 2.5f };

		float m_RunTimer{ 0 };
		float m_RunDuration{ 2.f };

		float m_JumpTimer{ 0 };
		float m_JumpDuration{ 4.f };

		float m_StartX;
		float m_StartY;

		float m_CurrentXSpeed{};
		float m_CurrentYSpeed{};

		const float m_MoveSpeed{ 150.f };
		const float m_MoveSpeedFalling{ 75.f };

		const float m_JumpSpeed{ 300.f };
		const float m_AirDecelerationSpeed{ 525.f };
		const float m_MaxFallSpeed{ 300.f };

		EnemyFacingDirection m_Direction{};
		EnemyFacingDirection m_StartDirection{};

		bool m_IsGrounded{ true };

		ISoundSystem* m_pSoundSystem{ nullptr };
	};
}