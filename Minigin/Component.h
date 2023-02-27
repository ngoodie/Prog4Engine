#pragma once
namespace dae
{
	class GameObject;
	class Component
	{
	public:
		virtual void Update(float deltaTime) = 0;
		virtual void FixedUpdate(float deltaTime) = 0;// {};
		virtual void Render() const = 0;

		Component() = default;
		virtual ~Component() {};
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		GameObject* m_pGameObject = nullptr;
		//std::string m_Id;
	};
}