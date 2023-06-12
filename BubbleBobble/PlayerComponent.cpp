#include "PlayerComponent.h"
#include "GameObject.h"
#include "AnimatedTextureComponent.h"
#include "LevelComponent.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "ServiceLocator.h"
#include "GameEvents.h"

dae::PlayerComponent::~PlayerComponent()
{

}

void dae::PlayerComponent::RegisterLevel(LevelComponent* pLevelComponent)
{
	m_pLevelComponent = pLevelComponent;
}

void dae::PlayerComponent::Initialize()
{
	m_pSoundSystem = &ServiceLocator::GetSoundSystem();

	GameObject* pGameObject = GetGameObject();
	pGameObject->SetPosition(m_StartX /* - m_SpriteOffset*/, m_StartY);

	m_pPlayerAnimTexComp = pGameObject->AddComponent(new AnimatedTextureComponent("player" + std::to_string(m_SpriteId) + ".png", 64, 64, 8, 5));
	pGameObject->AddComponent(new ColliderComponent(32, 32, false, m_SpriteOffset, 32));
	m_pRigidBodyComponent = pGameObject->AddComponent(new RigidbodyComponent());

	SetState(PlayerState::IDLE);
}

void dae::PlayerComponent::Move(float dirX, float dirY)
{
	if (m_State == PlayerState::DEAD || m_State == PlayerState::IN_BUBBLE)
		return;

	if (dirX > 0)
	{
		m_Direction = FacingDirection::RIGHT;
	}
	else if (dirX < 0)
	{
		m_Direction = FacingDirection::LEFT;
	}
	m_pPlayerAnimTexComp->SetFlipped(bool(m_Direction));

	if (m_State == PlayerState::FALLING)
	{
		m_CurrentXSpeed = dirX * m_MoveSpeed; //m_MoveSpeedFalling;
	}
	else
	{
		m_CurrentXSpeed = dirX * m_MoveSpeed;
		if (fabs(dirY) > FLT_EPSILON)
		{
			if (m_State != PlayerState::JUMPING)
			{
				m_pSoundSystem->Play(2, 1.f);

				m_CurrentYSpeed = -dirY * m_JumpSpeed;
				SetState(PlayerState::JUMPING);
			}
		}
	}

	if (m_State == PlayerState::IDLE)
	{
		SetState(PlayerState::RUNNING);
	}
}

void dae::PlayerComponent::ExitState()
{
	switch (m_State)
	{
	case PlayerState::SHOOT_BUBBLE:
		if (!m_IsGrounded)
		{
			if (m_CurrentYSpeed > 0)
			{
				m_State = PlayerState::FALLING;
				EnterState();
			}
			else
			{
				m_State = PlayerState::JUMPING;
				m_pPlayerAnimTexComp->SetSpritesPerSecond(8);
				m_pPlayerAnimTexComp->Play(5, 6);
			}
		}
		else if (fabs(m_CurrentYSpeed > 0))
		{
			m_State = PlayerState::RUNNING;
			EnterState();
		}
		else
		{
			m_State = PlayerState::IDLE;
			EnterState();
		}
		break;
	default:
		break;
	}
}

void dae::PlayerComponent::EnterState()
{
	switch (m_State)
	{
	case PlayerState::IDLE:
		m_pPlayerAnimTexComp->SetSpritesPerSecond(1);
		m_pPlayerAnimTexComp->Play(0, 0);
		break;
	case PlayerState::RUNNING:
		m_pPlayerAnimTexComp->SetSpritesPerSecond(16);
		m_pPlayerAnimTexComp->Play(1, 4);
		break;
	case PlayerState::JUMPING:
		m_IsGrounded = false;
		m_pPlayerAnimTexComp->SetSpritesPerSecond(8);
		m_pPlayerAnimTexComp->Play(5, 6);
		break;
	case PlayerState::FALLING:
		m_pPlayerAnimTexComp->SetSpritesPerSecond(8);
		m_pPlayerAnimTexComp->Play(7, 8);
		break;
	case PlayerState::DEAD:
		m_DeathTimer = 0;
		m_pPlayerAnimTexComp->SetSpritesPerSecond(8);
		m_pPlayerAnimTexComp->Play(13, 23);
		break;
	case PlayerState::SHOOT_BUBBLE:
		m_ShootTimer = 0;
		m_pPlayerAnimTexComp->SetSpritesPerSecond(12);
		m_pPlayerAnimTexComp->Play(9, 12);
		break;
	default:
		break;
	}
}

void dae::PlayerComponent::ShootBubble()
{
	if (m_State == PlayerState::SHOOT_BUBBLE || m_State == PlayerState::DEAD)
		return;

	m_pSoundSystem->Play(3, 1.f);
	SetState(PlayerState::SHOOT_BUBBLE);
}

void dae::PlayerComponent::Update(float deltaTime)
{
	switch (m_State)
	{
	default:
		break;
	case PlayerState::RUNNING:
		if (!m_IsGrounded)
		{
			SetState(PlayerState::FALLING);
		}
		else if (fabs(m_CurrentXSpeed) < FLT_EPSILON)
		{
			SetState(PlayerState::IDLE);
		}
		break;
	case PlayerState::JUMPING:
		if (m_CurrentYSpeed > 0)
		{
			SetState(PlayerState::FALLING);
		}
		break;
	case PlayerState::FALLING:
		if (m_IsGrounded)
		{
			SetState(PlayerState::IDLE);
		}
		break;
	case PlayerState::DEAD:
		m_DeathTimer += deltaTime;
		if (m_DeathTimer >= m_DeathDuration)
		{
			if (m_Lives > 0)
			{
				m_Lives--;
				NotifyObservers(static_cast<unsigned>(PlayerEvents::DIED));
				GetGameObject()->SetPosition(m_StartX, m_StartY);
				SetState(PlayerState::IDLE);
			}
			else
			{
				//GAME OVER
			}
			m_DeathTimer = 0;
		}
	case PlayerState::SHOOT_BUBBLE:
		m_ShootTimer += deltaTime;
		if (m_ShootTimer >= m_ShootDuration)
		{
			m_ShootTimer = 0;
			ExitState();
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
	else
	{
		//m_CurrentYSpeed = 0;
	}
}

void dae::PlayerComponent::FixedUpdate(float)
{

}