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

#include "SoundCommand.h"
#include "GameCommands.h"

//using namespace dae;

namespace dae
{
	void load()
	{
		float screenWidth = 256 * 2;
		float screenHeight = 224 * 2;

		auto& soundSystem = ServiceLocator::GetSoundSystem();
		soundSystem.RegisterSound(0, "../Data/opening_sfx.wav");
		soundSystem.RegisterSound(1, "../Data/insert_coin.wav");
		soundSystem.RegisterMusic(0, "../Data/music_test.wav");
		//soundSystem.PlayMusic(0, 1.f, -1);

		auto& input = InputManager::GetInstance();
		auto arcadeFont = ResourceManager::GetInstance().LoadFont("Emulogic.ttf", 16);

		/*
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
		*/
		
		// MainMenu Scene
		auto& pMainMenuScene = SceneManager::GetInstance().CreateScene("MainMenu");

		// Game Logo
		auto pLogoGo = std::make_shared<GameObject>();
		auto pLogoAnimTexComp = pLogoGo->AddComponent(new AnimatedTextureComponent("logo_animated.png", 356, 288, 3, 2));
		pLogoAnimTexComp->SetSpritesPerSecond(30);
		pLogoAnimTexComp->Play(0, 5);
		pLogoGo->SetPosition(screenWidth / 2.f - pLogoAnimTexComp->GetSpriteWidth() / 2.f, 30.f);
		pMainMenuScene.Add(pLogoGo);

		// Company logo
		auto pTaitoGo = std::make_shared<GameObject>();
		auto pTaitoAnimTexComp = pTaitoGo->AddComponent(new AnimatedTextureComponent("taito_dae.png", 144, 30, 4, 2));
		pTaitoAnimTexComp->SetSpritesPerSecond(2);
		pTaitoAnimTexComp->Play(0, 6, false, true);
		pTaitoGo->SetPosition(screenWidth / 2.f - pTaitoAnimTexComp->GetSpriteWidth() / 2.f, 322.f);
		pMainMenuScene.Add(pTaitoGo);

		// Bottom Text
		auto pMenuTextGo = std::make_shared<GameObject>();
		auto pMenuTextComp = pMenuTextGo->AddComponent(new TextComponent("© TAITO CORPORATION 1986", arcadeFont, 255, 255, 255));
		pMenuTextGo->SetPosition(screenWidth / 2.f - pMenuTextComp->GetWidth() / 2.f, 364);
		pMenuTextComp->SetSecondaryText("© HOWEST DAE 2023");
		pMenuTextComp->RecenterOnDraw(true, screenWidth);
		pMenuTextComp->SetColorOverTime(255, 255, 255, 0, 0, 0, 1.f / (2.f / 3.f), 2, true);
		pMainMenuScene.Add(pMenuTextGo);

		pMenuTextGo = std::make_shared<GameObject>();
		pMenuTextComp = pMenuTextGo->AddComponent(new TextComponent("ALL RIGHTS RESERVED", arcadeFont, 255, 255, 255));
		pMenuTextGo->SetPosition(screenWidth / 2.f - pMenuTextComp->GetWidth() / 2.f, 396);
		pMenuTextComp->SetSecondaryText("POWERED BY DUVEL ENGINE");
		pMenuTextComp->RecenterOnDraw(true, screenWidth);
		pMenuTextComp->SetColorOverTime(255, 255, 255, 0, 0, 0, 1.f / (2.f / 3.f), 2, true);
		pMainMenuScene.Add(pMenuTextGo);

		// UI Text
		auto p1UpGo = std::make_shared<GameObject>();
		auto p1UpTextComp = p1UpGo->AddComponent(new TextComponent("1UP", arcadeFont, 0, 255, 0));
		p1UpGo->SetPosition(88 - p1UpTextComp->GetWidth() / 2.f, -4.f);
		pMainMenuScene.Add(p1UpGo);

		auto p1ScoreGo = std::make_shared<GameObject>();
		auto p1ScoreTextComp = p1ScoreGo->AddComponent(new TextComponent("   00", arcadeFont, 255, 255, 255));
		p1ScoreGo->SetPosition(88 - p1ScoreTextComp->GetWidth() / 2.f, 12.f);
		pMainMenuScene.Add(p1ScoreGo);

		auto pHighScoreTitleGo = std::make_shared<GameObject>();
		auto pHighScoreTitleTextComp = pHighScoreTitleGo->AddComponent(new TextComponent("HIGH SCORE", arcadeFont, 255, 0, 0));
		pHighScoreTitleGo->SetPosition(screenWidth / 2.f - pHighScoreTitleTextComp->GetWidth() / 2.f, -4.f);
		pMainMenuScene.Add(pHighScoreTitleGo);

		auto pHighScoreGo = std::make_shared<GameObject>();
		auto pHighScoreTextComp = pHighScoreGo->AddComponent(new TextComponent(" 30000", arcadeFont, 255, 255, 255));
		pHighScoreGo->SetPosition(screenWidth / 2.f - pHighScoreTextComp->GetWidth() / 2.f, 12.f);
		pMainMenuScene.Add(pHighScoreGo);

		auto p2UpGo = std::make_shared<GameObject>();
		auto p2UpTextComp = p2UpGo->AddComponent(new TextComponent("2UP", arcadeFont, 0, 187, 255));
		p2UpGo->SetPosition(screenWidth - 88 - p2UpTextComp->GetWidth() / 2.f, -4.f);
		pMainMenuScene.Add(p2UpGo);

		auto p2ScoreGo = std::make_shared<GameObject>();
		auto p2ScoreTextComp = p2ScoreGo->AddComponent(new TextComponent("   00", arcadeFont, 255, 255, 255));
		p2ScoreGo->SetPosition(screenWidth - 88 - p2ScoreTextComp->GetWidth() / 2.f, 12.f);
		pMainMenuScene.Add(p2ScoreGo);

		// Commands
		Command* pSkipLogoCommand = new MM_SkipLogoCommand(pLogoGo.get(), soundSystem, 0, 1.f);
		input.AddControllerCommand(pMainMenuScene.GetId(), 0, ControllerButton::Start, PressType::DOWN, pSkipLogoCommand);

		// Restart Function
		auto RestartMainMenu = [&soundSystem, pLogoGo]()
		{
			soundSystem.Play(0, 1.f);
			pLogoGo->SetActive(true);
			std::cout << "restarted main menu\n";
		};
		pMainMenuScene.SetRestartFunction(RestartMainMenu);

		// Intro Scene
		auto& pIntroScene = SceneManager::GetInstance().CreateScene("Intro");

		Command* pSoundCommand = new SoundCommand(soundSystem, 0, 1.f);
		input.AddControllerCommand(pIntroScene.GetId(), 0, ControllerButton::ButtonB, PressType::DOWN, pSoundCommand);

		pSoundCommand = new SoundCommand(soundSystem, 1, 1.f);
		input.AddControllerCommand(pIntroScene.GetId(), 0, ControllerButton::ButtonB, PressType::UP, pSoundCommand);

		auto pBackgroundStars = std::make_shared<GameObject>();
		auto pStarsAnimTexComp = pBackgroundStars->AddComponent(new AnimatedTextureComponent("stars_animated.png", static_cast<int>(screenWidth), static_cast<int>(screenHeight), 2, 2));
		pStarsAnimTexComp->SetSpritesPerSecond(3);
		pStarsAnimTexComp->Play(0, 3, false, true);
		pIntroScene.Add(pBackgroundStars);

		// Text
		auto pTextGo = std::make_shared<GameObject>();
		auto pTextComp = pTextGo->AddComponent(new TextComponent("NOW,IT IS BEGINNING OF A", arcadeFont, 0, 0, 0));
		pTextComp->SetColorOverTime(0, 0, 0, 255, 0, 0, 2.0f);
		pTextGo->SetPosition(screenWidth / 2.f - pTextComp->GetWidth() / 2.f, 28);
		pIntroScene.Add(pTextGo);

		pTextGo = std::make_shared<GameObject>();
		pTextComp = pTextGo->AddComponent(new TextComponent("FANTASTIC STORY!! LET'S MAKE A", arcadeFont, 255, 0, 0));
		pTextComp->SetColorOverTime(0, 0, 0, 255, 0, 0, 2.0f);
		pTextGo->SetPosition(screenWidth / 2.f - pTextComp->GetWidth() / 2.f, 60);
		pIntroScene.Add(pTextGo);

		pTextGo = std::make_shared<GameObject>();
		pTextComp = pTextGo->AddComponent(new TextComponent("JOURNEY TO THE CAVE OF MONSTERS!", arcadeFont, 255, 0, 0));
		pTextComp->SetColorOverTime(0, 0, 0, 255, 0, 0, 2.0f);
		pTextGo->SetPosition(screenWidth / 2.f - pTextComp->GetWidth() / 2.f, 92);
		pIntroScene.Add(pTextGo);

		pTextGo = std::make_shared<GameObject>();
		pTextComp = pTextGo->AddComponent(new TextComponent("GOOD LUCK!", arcadeFont, 255, 0, 0));
		pTextComp->SetColorOverTime(0, 0, 0, 255, 0, 0, 2.0f);
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
		Command* pTestCommand2 = new TestCommand(pPlayerOne.get());
		input.AddKeyboardCommand(pIntroScene.GetId(), SDL_SCANCODE_Y, PressType::DOWN, pTestCommand2);

		SceneManager::GetInstance().SetScene("MainMenu", true);
	}
}

int main(int, char* [])
{
	ServiceLocator::RegisterSoundSystem(std::make_unique<SDLSoundSystem>());

	dae::Minigin engine("../Data/");
	engine.Run(dae::load);
	return 0;
}