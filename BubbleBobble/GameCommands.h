#pragma once
#include "Command.h"

class ISoundSystem;
namespace dae
{
	class MM_Confirm final : public Command
	{
	public:
		MM_Confirm(GameObject* pGameObject, ISoundSystem& pSoundSystem, unsigned short soundId, float volume)
			: Command(pGameObject)
			, m_SoundId{ soundId }
			, m_Volume{ volume }
			, m_pSoundSystem{ pSoundSystem }
		{};

		~MM_Confirm() override = default;
		void Execute() override;

	private:
		unsigned short m_SoundId;
		float m_Volume;
		ISoundSystem& m_pSoundSystem;
	};

	class MM_Select final : public Command
	{
	public:
		MM_Select(GameObject* pGameObject, int selectionChange)
			: Command(pGameObject)
			, m_SelectionChange{ selectionChange }
		{};

		~MM_Select() override = default;
		void Execute() override;

	private:
		int m_SelectionChange;
	};

	class MM_Back final : public Command
	{
	public:
		MM_Back(GameObject* pGameObject)
			: Command(pGameObject)
		{};

		~MM_Back() override = default;
		void Execute() override;
	};

	class TestCommand final : public Command
	{
	public:
		TestCommand(GameObject* pGameObject) : Command(pGameObject) {};
		~TestCommand() override = default;

		void Execute() override;
	};
}