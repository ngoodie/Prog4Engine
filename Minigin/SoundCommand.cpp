#include "SoundCommand.h"
#include "ISoundSystem.h"

void dae::SoundCommand::Execute()
{
	m_pSoundSystem.Play(m_SoundId, m_Volume);
}