#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		bool SetScene(const std::string& name, bool restart = false);

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render();
		unsigned int GetActiveSceneId() const { return m_ActiveSceneId; }

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		std::vector<std::shared_ptr<Scene>> m_pScenes;
		unsigned int m_ActiveSceneId{ 0 };
	};
}