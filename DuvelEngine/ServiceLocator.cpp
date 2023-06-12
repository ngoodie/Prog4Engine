#include "ServiceLocator.h"
std::unique_ptr<ISoundSystem> ServiceLocator::m_pSoundSystemInstance = std::make_unique<NullSoundSystem>();