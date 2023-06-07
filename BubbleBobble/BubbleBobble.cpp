#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "Scene.h"

#include "FPSComponent.h"
#include "RotatorComponent.h"

#include "InputManager.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::TextureComponent("background.tga"));
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::TextureComponent("logo.tga"));
	go->SetPosition(216, 180);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent(new dae::TextComponent("Programming 4 Assignment", font));
	go->SetPosition(80, 20);
	scene.Add(go);

	// FPS Counter
	go = std::make_shared<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);
	go->AddComponent(new dae::TextComponent("0", font));
	go->AddComponent(new dae::FPSComponent());
	//go->RemoveComponent<dae::FPSComponent>();
	go->SetPosition(10, 10);
	scene.Add(go);

	// Sprite#2
	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::RotatorComponent(20.f, 7.5f, true));
	go->AddComponent(new dae::TextureComponent("pacman2.png"));
	//go->SetParent(pSprite1);
	go->SetPosition(20, 20);
	auto pSprite2 = go.get();
	scene.Add(go);

	// Sprite#1
	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::RotatorComponent(20.f, 7.5f, false));
	go->AddComponent(new dae::TextureComponent("pacman.png"));
	auto pSprite1 = go.get();
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->SetPosition(100, 100);
	go->AddChild(pSprite1);
	scene.Add(go);

	pSprite1->AddChild(pSprite2);

	//command/input test
	dae::Command* pTestCommand = new dae::TestCommand(pSprite1);

	auto& input = dae::InputManager::GetInstance();
	input.AddControllerCommand(0, dae::ContollerButton::ButtonA, pTestCommand);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}