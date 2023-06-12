#include "ZenChanComponent.h"
#include "GameObject.h"
#include "AnimatedTextureComponent.h"
#include "LevelComponent.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "ServiceLocator.h"
#include "GameEvents.h"

dae::ZenChanComponent::~ZenChanComponent()
{

}

void dae::ZenChanComponent::RegisterLevel(LevelComponent* pLevelComponent)
{
	m_pLevelComponent = pLevelComponent;
}

void dae::ZenChanComponent::Initialize()
{
	m_pSoundSystem = &ServiceLocator::GetSoundSystem();

	GameObject* pGameObject = GetGameObject();
	pGameObject->SetPosition(m_StartX, m_StartY);

	m_pAnimTexComp = pGameObject->AddComponent(new AnimatedTextureComponent("zenchan.png", 32, 32, 16, 2));
	pGameObject->AddComponent(new ColliderComponent(32, 32, false));
	m_pRigidBodyComponent = pGameObject->AddComponent(new RigidbodyComponent());

	m_pAnimTexComp->SetFlipped(bool(m_Direction));

	SetState(ZenChanState::RUNNING);
}

void dae::ZenChanComponent::Reset()
{
	m_FreezeTimer = 2.5f;
	m_RunTimer = 0.f;
	m_JumpTimer = 0.f;
	GetGameObject()->SetPosition(m_StartX, m_StartY);

	m_Direction = m_StartDirection;
	m_pAnimTexComp->SetFlipped(bool(m_Direction));

	SetState(ZenChanState::RUNNING);
}

void dae::ZenChanComponent::Move(float dirX, float dirY)
{
	if (m_State == ZenChanState::DEAD || m_State == ZenChanState::IN_BUBBLE_1 || m_State == ZenChanState::IN_BUBBLE_2 || m_State == ZenChanState::IN_BUBBLE_3 || m_FreezeTimer > 0)
		return;

	if (dirX > 0)
	{
		m_Direction = EnemyFacingDirection::RIGHT;
	}
	else if (dirX < 0)
	{
		m_Direction = EnemyFacingDirection::LEFT;
	}
	m_pAnimTexComp->SetFlipped(bool(m_Direction));

	m_CurrentXSpeed = dirX * m_MoveSpeed;
	if (fabs(dirY) > FLT_EPSILON)
	{
		m_CurrentYSpeed = -dirY * m_JumpSpeed;
	}
}

void dae::ZenChanComponent::ExitState()
{

}

void dae::ZenChanComponent::EnterState()
{
	switch (m_State)
	{
	case ZenChanState::RUNNING:
		m_pAnimTexComp->SetSpritesPerSecond(16);
		m_pAnimTexComp->Play(0, 3);
		break;
	default:
		break;
	}
}

void dae::ZenChanComponent::Update(float deltaTime)
{
	if (m_FreezeTimer > 0)
	{
		m_FreezeTimer -= deltaTime;
		return;
	}

	switch (m_State)
	{
	default:
		break;
	case ZenChanState::RUNNING:
		m_JumpTimer += deltaTime;
		if (m_JumpTimer >= m_JumpDuration)
		{
			Move(0, 1.f);
			m_JumpTimer = 0;
		}

		m_RunTimer += deltaTime;
		if (m_RunTimer >= m_RunDuration)
		{
			if (m_Direction == EnemyFacingDirection::LEFT)
			{
				m_Direction = EnemyFacingDirection::RIGHT;
			}
			else
			{
				m_Direction = EnemyFacingDirection::LEFT;
			}
			m_RunTimer = 0;
		}

		if (m_Direction == EnemyFacingDirection::LEFT)
		{
			Move(-1.f, 0);
		}
		else
		{
			Move(1.f, 0);
		}

		break;
	}

	if (m_CurrentYSpeed < 0)
	{
		m_IsGrounded = m_pRigidBodyComponent->Move(m_CurrentXSpeed * deltaTime, m_CurrentYSpeed * deltaTime, m_pLevelComponent->GetBorderColliders());
	}
	else
	{
		m_IsGrounded = m_pRigidBodyComponent->Move(m_CurrentXSpeed * deltaTime, m_CurrentYSpeed * deltaTime, m_pLevelComponent->GetNearbyLevelTileColliders());
	}

	auto pos = GetGameObject()->GetWorldPosition();
	if (pos.y > 448.f)
	{
		GetGameObject()->SetPosition(pos.x, 0 - 32.f);
	}

	if (m_CurrentXSpeed < 0)
	{
		m_CurrentXSpeed += m_MoveSpeed;
		if (m_CurrentXSpeed > 0) m_CurrentXSpeed = 0;
	}
	else if (m_CurrentXSpeed > 0)
	{
		m_CurrentXSpeed -= m_MoveSpeed;
		if (m_CurrentXSpeed < 0) m_CurrentXSpeed = 0;
	}

	if (!m_IsGrounded)
	{
		m_CurrentYSpeed += m_AirDecelerationSpeed * deltaTime;
		if (m_CurrentYSpeed > m_MaxFallSpeed) m_CurrentYSpeed = m_MaxFallSpeed;
	}
}

void dae::ZenChanComponent::FixedUpdate(float)
{

}