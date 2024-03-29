#pragma once
#include <iostream>

namespace dae
{
	class GameObject;

	class Command
	{
	public:
		Command(GameObject* pGameObject) { m_pGameObject = pGameObject; }
		virtual ~Command() = default;

		virtual void Execute() = 0;
	protected:
		GameObject* GetGameObject() const { return m_pGameObject; }
	private:
		GameObject* m_pGameObject{ nullptr };

	};
}