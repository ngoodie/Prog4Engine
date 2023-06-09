#pragma once
#include "Command.h"

class ISoundSystem;
namespace dae
{
	class SoundCommand final : public Command
	{
	public:
		SoundCommand(ISoundSystem& pSoundSystem, unsigned short soundId, float volume)
			: Command(nullptr)
			, m_SoundId{ soundId }
			, m_Volume{ volume }
			, m_pSoundSystem{ pSoundSystem }
		{};

		~SoundCommand() override = default;

		void Execute() override;

	private:
		unsigned short m_SoundId;
		float m_Volume;
		ISoundSystem& m_pSoundSystem;
	};
}