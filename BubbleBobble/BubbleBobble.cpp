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
#include "AnimatedTextureComponent.h"
#include "TextComponent.h"
#include "Scene.h"

#include "FPSComponent.h"
#include "RotatorComponent.h"
#include "BubblesGeneratorComponent.h"

#include "InputManager.h"

#include "ServiceLocator.h"
#include "SDLSoundSystem.h"

//using namespace dae;

namespace dae
{
	void load()
	{
		float screenWidth = 256 * 2;
		float screenHeight = 224 * 2;

		auto& input = InputManager::GetInstance();

		// Scene #1
		auto& pDemoScene = SceneManager::GetInstance().CreateScene("Demo");

		// Background
		auto pBackgroundGo = std::make_shared<GameObject>();
		pBackgroundGo->AddComponent(new TextureComponent("background.tga"));
		pDemoScene.Add(pBackgroundGo);

		// Logo
		auto pLogoGo = std::make_shared<GameObject>();
		pLogoGo->AddComponent(new TextureComponent("logo.tga"));
		pLogoGo->SetPosition(216, 180);
		pDemoScene.Add(pLogoGo);

		// Text
		auto pHeadTextGo = std::make_shared<GameObject>();
		auto pFont36 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		pHeadTextGo->AddComponent(new TextComponent("Programming 4 Assignment", pFont36, 255, 255, 255));
		pHeadTextGo->SetPosition(80, 20);
		pDemoScene.Add(pHeadTextGo);

		// FPS Counter
		auto pFpsGo = std::make_shared<GameObject>();
		auto pFont14 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);
		pFpsGo->AddComponent(new TextComponent("0", pFont14, 255, 255, 255));
		pFpsGo->AddComponent(new FPSComponent());
		pFpsGo->SetPosition(10, 10);
		pDemoScene.Add(pFpsGo);

		// Sprite#1
		auto pSprite1 = std::make_shared<GameObject>();
		pSprite1->AddComponent(new RotatorComponent(20.f, 7.5f, false));
		pSprite1->AddComponent(new TextureComponent("pacman.png"));

		// Sprite#2
		auto pSprite2 = std::make_shared<GameObject>();
		pSprite2->AddComponent(new RotatorComponent(20.f, 7.5f, true));
		pSprite2->AddComponent(new TextureComponent("pacman2.png"));
		pSprite1->AddChild(pSprite2);

		auto pAnchorGo = std::make_shared<GameObject>();
		pAnchorGo->SetPosition(100, 100);
		pAnchorGo->AddChild(pSprite1);
		pDemoScene.Add(pAnchorGo);

		// Commands
		Command* pTestCommand = new TestCommand(pSprite1.get());

		input.AddControllerCommand(pDemoScene.GetId(), 0, ControllerButton::ButtonA, PressType::HELD, pTestCommand);

		pTestCommand = new TestCommand(pSprite1.get());
		input.AddKeyboardCommand(pDemoScene.GetId(), SDL_SCANCODE_A, PressType::DOWN, pTestCommand);
		
		// Scene #2

		auto& soundSystem = ServiceLocator::GetSoundSystem();
		soundSystem.RegisterSound(0, "../Data/test.wav");
		soundSystem.Play(0, 100);

		auto arcadeFont = ResourceManager::GetInstance().LoadFont("Emulogic.ttf", 16);
		auto& pIntroScene = SceneManager::GetInstance().CreateScene("Intro");

		auto pBackgroundStars = std::make_shared<GameObject>();
		auto pStarsAnimTexComp = pBackgroundStars->AddComponent(new AnimatedTextureComponent("stars_animated.png", static_cast<int>(screenWidth), static_cast<int>(screenHeight), 2, 2));
		pStarsAnimTexComp->SetSpritesPerSecond(2);
		pStarsAnimTexComp->Play(0, 3, false, true);
		pIntroScene.Add(pBackgroundStars);

		// Text
		auto pTextGo = std::make_shared<GameObject>();
		auto pTextComp = pTextGo->AddComponent(new TextComponent("NOW,IT IS BEGINNING OF A", arcadeFont, 0, 0, 0));
		pTextComp->SetColorOverTime(0, 0, 0, 255, 0, 0, 2.5f);
		pTextGo->SetPosition(screenWidth / 2.f - pTextComp->GetWidth() / 2.f, 28);
		pIntroScene.Add(pTextGo);

		pTextGo = std::make_shared<GameObject>();
		pTextComp = pTextGo->AddComponent(new TextComponent("FANTASTIC STORY!! LET'S MAKE A", arcadeFont, 255, 0, 0));
		pTextComp->SetColorOverTime(0, 0, 0, 255, 0, 0, 2.5f);
		pTextGo->SetPosition(screenWidth / 2.f - pTextComp->GetWidth() / 2.f, 60);
		pIntroScene.Add(pTextGo);

		pTextGo = std::make_shared<GameObject>();
		pTextComp = pTextGo->AddComponent(new TextComponent("JOURNEY TO THE CAVE OF MONSTERS!", arcadeFont, 255, 0, 0));
		pTextComp->SetColorOverTime(0, 0, 0, 255, 0, 0, 2.5f);
		pTextGo->SetPosition(screenWidth / 2.f - pTextComp->GetWidth() / 2.f, 92);
		pIntroScene.Add(pTextGo);

		pTextGo = std::make_shared<GameObject>();
		pTextComp = pTextGo->AddComponent(new TextComponent("GOOD LUCK!", arcadeFont, 255, 0, 0));
		pTextComp->SetColorOverTime(0, 0, 0, 255, 0, 0, 2.5f);
		pTextGo->SetPosition(screenWidth / 2.f - pTextComp->GetWidth() / 2.f, 124);
		pIntroScene.Add(pTextGo);

		// Rotating players
		auto pPlayerOne = std::make_shared<GameObject>();
		auto pAnimTexComp = pPlayerOne->AddComponent(new AnimatedTextureComponent("player1.png", 64, 64, 8, 5));
		pAnimTexComp->SetSpritesPerSecond(5);
		pAnimTexComp->Play(30, 31);
		pPlayerOne->AddComponent(new RotatorComponent(16.f, 4.f, false));

		auto pPlayerOneRotationPointGo = std::make_shared<GameObject>();
		pPlayerOneRotationPointGo->SetPosition(screenWidth / 4 - pAnimTexComp->GetSpriteWidth() / 2.f, screenHeight / 2 - pAnimTexComp->GetSpriteHeight() / 2.f);
		pPlayerOneRotationPointGo->AddChild(pPlayerOne);
		pIntroScene.Add(pPlayerOneRotationPointGo);

		auto pPlayerTwo = std::make_shared<GameObject>();
		pAnimTexComp = pPlayerTwo->AddComponent(new AnimatedTextureComponent("player2.png", 64, 64, 8, 5));
		pAnimTexComp->SetSpritesPerSecond(5);
		pAnimTexComp->Play(30, 31);
		pPlayerTwo->AddComponent(new RotatorComponent(16.f, 4.f, true));

		auto pPlayerTwoRotationPointGo = std::make_shared<GameObject>();
		pPlayerTwoRotationPointGo->SetPosition(screenWidth - screenWidth / 4 - pAnimTexComp->GetSpriteWidth() / 2.f, screenHeight / 2 - pAnimTexComp->GetSpriteHeight() / 2.f);
		pPlayerTwoRotationPointGo->AddChild(pPlayerTwo);
		pIntroScene.Add(pPlayerTwoRotationPointGo);

		// Bubbles
		auto pBubblesGenerator = std::make_shared<GameObject>();
		pBubblesGenerator->AddComponent(new BubblesGeneratorComponent(1 / 20.f, 17.5f, 200.f, 50));
		pBubblesGenerator->SetPosition(screenWidth / 2, screenHeight / 2);
		pIntroScene.Add(pBubblesGenerator);

		// Commands
		pTestCommand = new TestCommand(pPlayerOne.get());
		input.AddKeyboardCommand(pIntroScene.GetId(), SDL_SCANCODE_Y, PressType::DOWN, pTestCommand);

		SceneManager::GetInstance().SetScene("Intro");
	}
}

int main(int, char* [])
{
	ServiceLocator::RegisterSoundSystem(std::make_unique<SDLSoundSystem>());

	dae::Minigin engine("../Data/");
	engine.Run(dae::load);
	return 0;
}