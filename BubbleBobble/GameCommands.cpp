#include "GameCommands.h"
#include "GameObject.h"
#include "ISoundSystem.h"
#include "SceneManager.h"

void dae::MM_SkipLogoCommand::Execute()
{
	GameObject* pLogoGo = GetGameObject();
	if (pLogoGo->IsActive())
	{
		GetGameObject()->SetActive(false);
		//m_pSoundSystem.Play(m_SoundId, m_Volume);
		SceneManager::GetInstance().SetScene("Intro");
	}
}