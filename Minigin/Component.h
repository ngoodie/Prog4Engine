#pragma once
namespace dae
{
	class GameObject;
	class Component
	{
	public:
		virtual void Update(float deltaTime) = 0;
		virtual void FixedUpdate(float deltaTime) = 0; //{};
		virtual void Render() const = 0;

		Component() = default;
		virtual ~Component() {};
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		void InitializeGameObject(GameObject* pGo)
		{
			if (m_pGameObject == nullptr)
			{
				m_pGameObject = pGo;
			}
		};

	protected:
		GameObject* GetGameObject() const { return m_pGameObject; };

	private:
		GameObject* m_pGameObject = nullptr;
		//TODO:
		bool m_bMarkedForDeletion{ false };
	};
}