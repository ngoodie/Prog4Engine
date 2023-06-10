#include "SceneManager.h"
#include "Scene.h"

bool dae::SceneManager::SetScene(const std::string& name, bool restart)
{
	for (const auto& pScene : m_pScenes)
	{
		if (pScene->GetName() == name)
		{
			if (restart)
				pScene->Restart();

			m_ActiveSceneId = pScene->GetId();
			return true;
		}
	}

	return false;
}

void dae::SceneManager::Update(float deltaTime)
{
	for(auto& pScene : m_pScenes)
	{
		if (pScene->GetId() == m_ActiveSceneId)
		{
			pScene->Update(deltaTime);
			break;
		}
		//pScene->Update(deltaTime);
	}
}

void dae::SceneManager::FixedUpdate(float deltaTime)
{
	for (auto& pScene : m_pScenes)
	{
		if (pScene->GetId() == m_ActiveSceneId)
		{
			pScene->FixedUpdate(deltaTime);
			break;
		}
		//pScene->FixedUpdate(deltaTime);
	}
}

void dae::SceneManager::Render()
{
	for (auto& pScene : m_pScenes)
	{
		if (pScene->GetId() == m_ActiveSceneId)
		{
			pScene->Render();
			break;
		}
		//pScene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_pScenes.push_back(scene);

	return *scene;
}