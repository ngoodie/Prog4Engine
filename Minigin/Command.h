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

	class TestCommand final : public Command
	{
	public:
		TestCommand(GameObject* pGameObject) : Command(pGameObject) {};
		~TestCommand() override = default;

		void Execute() override { std::cout << "test command\n"; }
	};
}