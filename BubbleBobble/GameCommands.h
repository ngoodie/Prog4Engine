#pragma once
#include "Command.h"

class ISoundSystem;
namespace dae
{
	class MM_SkipLogoCommand final : public Command
	{
	public:
		MM_SkipLogoCommand(GameObject* pGameObject, ISoundSystem& pSoundSystem, unsigned short soundId, float volume)
			: Command(pGameObject)
			, m_SoundId{ soundId }
			, m_Volume{ volume }
			, m_pSoundSystem{ pSoundSystem }
		{};

		~MM_SkipLogoCommand() override = default;
		void Execute() override;

	private:
		unsigned short m_SoundId;
		float m_Volume;
		ISoundSystem& m_pSoundSystem;
	};
}