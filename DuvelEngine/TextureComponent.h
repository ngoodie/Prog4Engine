#pragma once
#include "Component.h"
#include "Texture2D.h"
//#include <string>
//#include <memory>

namespace dae
{
	class TextureComponent : public Component
	{
	public:
		TextureComponent(const std::string& filename);
		~TextureComponent() override;

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void Render() const override;

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
	};
}