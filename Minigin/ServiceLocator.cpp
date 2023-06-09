#include "ServiceLocator.h"
std::unique_ptr<ISoundSystem, std::default_delete<ISoundSystem>> ServiceLocator::m_pSoundSystemInstance = nullptr;