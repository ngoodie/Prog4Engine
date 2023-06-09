#pragma once
#include <memory>
#include "ISoundSystem.h"
#include "NullSoundSystem.h"

class ServiceLocator final
{
public:
	static ISoundSystem& GetSoundSystem()
	{
		return *m_pSoundSystemInstance;
	}

	static void RegisterSoundSystem (std::unique_ptr<ISoundSystem>&& pSoundSystem)
	{
		m_pSoundSystemInstance = pSoundSystem == nullptr ? std::make_unique<NullSoundSystem>() : std::move(pSoundSystem);
		//m_pSoundSystemInstance = std::move(pSoundSystem);
	}

private:
	static std::unique_ptr<ISoundSystem> m_pSoundSystemInstance;
};