#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;
	class FPSComponent : public Component
	{
	public:
		FPSComponent();
		~FPSComponent();

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override {};

	private:
		TextComponent* m_pTextComponent{ nullptr };
	};
}