#pragma once
class Component
{
public:
	virtual void Update(float deltaTime) = 0;
	virtual void FixedUpdate(float deltaTime) = 0;// {};
	virtual void Render() const = 0;

	Component() = default;
	virtual ~Component() = 0;
	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;
};