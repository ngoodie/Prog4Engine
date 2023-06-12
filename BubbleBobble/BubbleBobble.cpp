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
#include "MainMenuComponent.h"
#include "TimedSceneSwitchComponent.h"
#include "Scene.h"

#include "FPSComponent.h"
#include "RotatorComponent.h"
#include "BubblesGeneratorComponent.h"
#include "LevelComponent.h"
#include "TimedSetActiveComponent.h"
#include "PlayerComponent.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "PlayerLivesComponent.h"

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
		soundSystem.RegisterSound(0, "../Data/Sfx/opening.wav");
		soundSystem.RegisterSound(1, "../Data/Sfx/bublbobl-051_insert_coin.wav");
		soundSystem.RegisterSound(2, "../Data/Sfx/bublbobl-040_jump.wav");
		soundSystem.RegisterSound(3, "../Data/Sfx/bublbobl-047_shoot_bubble.wav");

		soundSystem.RegisterMusic(0, "../Data/Music/intro_music.mp3");
		soundSystem.RegisterMusic(1, "../Data/Music/main_theme.mp3");
		soundSystem.RegisterMusic(2, "../Data/Music/main_theme_hurry.mp3");
		soundSystem.RegisterMusic(3, "../Data/Music/game_over.mp3");
		soundSystem.RegisterMusic(4, "../Data/Music/highscore_screen.mp3");
		soundSystem.RegisterMusic(5, "../Data/Music/super_drunk.mp3");
		//soundSystem.PlayMusic(0, 1.f, 1);
		//soundSystem.PlayMusic(1, 1.f, -1);

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
		
		// **************
		// MainMenu Scene
		// **************
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

		// GameMode Selection Menu
		auto pGameModesContainerGo = std::make_shared<GameObject>();
		pMainMenuScene.Add(pGameModesContainerGo);

		pGameModesContainerGo->SetActive(false);

		// Select GameMode Title
		auto pGameModeTitleGo = std::make_shared<GameObject>();

		auto pGameModeTitleTextComp = pGameModeTitleGo->AddComponent(new TextComponent("- SELECT GAMEMODE -", arcadeFont, 255, 255, 255));
		pGameModeTitleGo->SetPosition(screenWidth / 2.f - pGameModeTitleTextComp->GetWidth() / 2.f, 92.f);
		pGameModesContainerGo->AddChild(pGameModeTitleGo);

		// 1 Player
		auto pSinglePlayerGo = std::make_shared<GameObject>();
		auto pSinglePlayerTextComp = pSinglePlayerGo->AddComponent(new TextComponent("1 PLAYER", arcadeFont, 255, 255, 255));
		pSinglePlayerGo->SetPosition(screenWidth / 2.f - pSinglePlayerTextComp->GetWidth() / 2.f, 156.f);
		pGameModesContainerGo->AddChild(pSinglePlayerGo);

		// 2 Player Co-Op
		auto pCoopGo = std::make_shared<GameObject>();
		auto pCoopTextComp = pCoopGo->AddComponent(new TextComponent("CO-OP", arcadeFont, 128, 128, 128));
		pCoopGo->SetPosition(screenWidth / 2.f - pCoopTextComp->GetWidth() / 2.f, 188.f);
		pGameModesContainerGo->AddChild(pCoopGo);

		// 2 Player Versus
		auto pVersusGo = std::make_shared<GameObject>();
		auto pVersusTextComp = pVersusGo->AddComponent(new TextComponent("VERSUS", arcadeFont, 128, 128, 128));
		pVersusGo->SetPosition(screenWidth / 2.f - pVersusTextComp->GetWidth() / 2.f, 220.f);
		pGameModesContainerGo->AddChild(pVersusGo);

		// Selection Arrow
		auto pSelectionArrowGo = std::make_shared<GameObject>();
		auto pSelectionArrowTexComp = pSelectionArrowGo->AddComponent(new AnimatedTextureComponent("selection_arrow.png", 16, 16, 2, 1));
		pSelectionArrowGo->SetPosition(pSinglePlayerGo->GetWorldPosition().x - 24.f, pSinglePlayerGo->GetWorldPosition().y + 2);
		pSelectionArrowTexComp->SetSpritesPerSecond(2);
		pSelectionArrowTexComp->Play(0, 1, false);
		pGameModesContainerGo->AddChild(pSelectionArrowGo);
		
		// MainMenuGo
		auto pMainMenuGo = std::make_shared<GameObject>();
		auto pMainMenuComp = pMainMenuGo->AddComponent(new MainMenuComponent(pLogoGo.get(), pGameModesContainerGo.get(), pSinglePlayerGo.get(), pCoopGo.get(), pVersusGo.get(), pSelectionArrowGo.get()));
		pMainMenuScene.Add(pMainMenuGo);

		// Commands
		Command* pMainMenuConfirmCommand = new MM_Confirm(pMainMenuGo.get(), soundSystem, 0, 1.f);
		input.AddControllerCommand(pMainMenuScene.GetId(), 0, ControllerButton::Start, PressType::DOWN, pMainMenuConfirmCommand);
		pMainMenuConfirmCommand = new MM_Confirm(pMainMenuGo.get(), soundSystem, 0, 1.f);
		input.AddControllerCommand(pMainMenuScene.GetId(), 0, ControllerButton::ButtonA, PressType::DOWN, pMainMenuConfirmCommand);

		Command* pMainMenuUpCommand = new MM_Select(pMainMenuGo.get(), -1);
		input.AddControllerCommand(pMainMenuScene.GetId(), 0, ControllerButton::DPadUp, PressType::DOWN, pMainMenuUpCommand);

		Command* pMainMenuDownCommand = new MM_Select(pMainMenuGo.get(), 1);
		input.AddControllerCommand(pMainMenuScene.GetId(), 0, ControllerButton::DPadDown, PressType::DOWN, pMainMenuDownCommand);

		Command* pMainMenuBackCommand = new MM_Back(pMainMenuGo.get());
		input.AddControllerCommand(pMainMenuScene.GetId(), 0, ControllerButton::Back, PressType::DOWN, pMainMenuBackCommand);

		// Restart Function
		auto RestartMainMenu = [&soundSystem, pMainMenuComp]()
		{
			soundSystem.StopMusic();
			soundSystem.Play(0, 1.f);
			pMainMenuComp->SetState(MainMenuState::LOGO);
			pMainMenuComp->SetSelection(0);

			std::cout << "restarted main menu\n";
		};
		pMainMenuScene.SetRestartFunction(RestartMainMenu);

		// ***********
		// Intro Scene
		// ***********
		auto& pIntroScene = SceneManager::GetInstance().CreateScene("Intro");

		Command* pSoundCommand = new SoundCommand(soundSystem, 0, 1.f);
		input.AddControllerCommand(pIntroScene.GetId(), 0, ControllerButton::ButtonB, PressType::DOWN, pSoundCommand);

		pSoundCommand = new SoundCommand(soundSystem, 1, 1.f);
		input.AddControllerCommand(pIntroScene.GetId(), 0, ControllerButton::ButtonB, PressType::UP, pSoundCommand);

		auto pBackgroundStars = std::make_shared<GameObject>();
		auto pStarsAnimTexComp = pBackgroundStars->AddComponent(new AnimatedTextureComponent("stars_animated.png", static_cast<int>(screenWidth), static_cast<int>(screenHeight), 2, 2));
		pStarsAnimTexComp->SetSpritesPerSecond(2);
		pStarsAnimTexComp->Play(0, 3, false, true);
		pIntroScene.Add(pBackgroundStars);

		// Text
		auto pTextGo = std::make_shared<GameObject>();
		auto pTextComp0 = pTextGo->AddComponent(new TextComponent("NOW,IT IS BEGINNING OF A", arcadeFont, 0, 0, 0));
		pTextComp0->SetColorOverTime(0, 0, 0, 255, 0, 0, 2.0f);
		pTextGo->SetPosition(screenWidth / 2.f - pTextComp0->GetWidth() / 2.f, 28);
		pIntroScene.Add(pTextGo);

		pTextGo = std::make_shared<GameObject>();
		auto pTextComp1 = pTextGo->AddComponent(new TextComponent("FANTASTIC STORY!! LET'S MAKE A", arcadeFont, 255, 0, 0));
		pTextComp1->SetColorOverTime(0, 0, 0, 255, 0, 0, 2.0f);
		pTextGo->SetPosition(screenWidth / 2.f - pTextComp1->GetWidth() / 2.f, 60);
		pIntroScene.Add(pTextGo);

		pTextGo = std::make_shared<GameObject>();
		auto pTextComp2 = pTextGo->AddComponent(new TextComponent("JOURNEY TO THE CAVE OF MONSTERS!", arcadeFont, 255, 0, 0));
		pTextComp2->SetColorOverTime(0, 0, 0, 255, 0, 0, 2.0f);
		pTextGo->SetPosition(screenWidth / 2.f - pTextComp2->GetWidth() / 2.f, 92);
		pIntroScene.Add(pTextGo);

		pTextGo = std::make_shared<GameObject>();
		auto pTextComp3 = pTextGo->AddComponent(new TextComponent("GOOD LUCK!", arcadeFont, 255, 0, 0));
		pTextComp3->SetColorOverTime(0, 0, 0, 255, 0, 0, 2.0f);
		pTextGo->SetPosition(screenWidth / 2.f - pTextComp3->GetWidth() / 2.f, 124);
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
		auto pBubblesGeneratorComp = pBubblesGenerator->AddComponent(new BubblesGeneratorComponent(1 / 20.f, 17.5f, 200.f, 80));
		pBubblesGenerator->SetPosition(screenWidth / 2, screenHeight / 2);
		pIntroScene.Add(pBubblesGenerator);

		// Next Scene Timer
		auto pNextSceneGo = std::make_shared<GameObject>();
		auto pTimedSceneSwitchComp = pNextSceneGo->AddComponent(new TimedSceneSwitchComponent(0.5f/*8.5f*/, "SinglePlayer", true));
		pIntroScene.Add(pNextSceneGo);

		// Commands
		Command* pTestCommand2 = new TestCommand(pPlayerOne.get());
		input.AddKeyboardCommand(pIntroScene.GetId(), SDL_SCANCODE_Y, PressType::DOWN, pTestCommand2);

		// Restart Function
		auto RestartIntro = [&soundSystem, pTextComp0, pTextComp1, pTextComp2, pTextComp3, pBubblesGeneratorComp, pTimedSceneSwitchComp]()
		{
			soundSystem.PlayMusic(0, 1.f, 1);
			pTextComp0->SetColorOverTime(0, 0, 0, 255, 0, 0, 2.0f);
			pTextComp1->SetColorOverTime(0, 0, 0, 255, 0, 0, 2.0f);
			pTextComp2->SetColorOverTime(0, 0, 0, 255, 0, 0, 2.0f);
			pTextComp3->SetColorOverTime(0, 0, 0, 255, 0, 0, 2.0f);
			pTimedSceneSwitchComp->ResetTimer();
			pBubblesGeneratorComp->Restart();

			std::cout << "restarted intro\n";
		};
		pIntroScene.SetRestartFunction(RestartIntro);

		// ******************
		// SinglePlayer Scene
		// ******************
		auto& pSinglePlayerScene = SceneManager::GetInstance().CreateScene("SinglePlayer");

		// UI Text
		p1UpGo = std::make_shared<GameObject>();
		p1UpTextComp = p1UpGo->AddComponent(new TextComponent("1UP", arcadeFont, 0, 255, 0));
		p1UpGo->SetPosition(88 - p1UpTextComp->GetWidth() / 2.f, -4.f);
		pSinglePlayerScene.Add(p1UpGo);

		p1ScoreGo = std::make_shared<GameObject>();
		p1ScoreTextComp = p1ScoreGo->AddComponent(new TextComponent("   00", arcadeFont, 255, 255, 255));
		p1ScoreGo->SetPosition(88 - p1ScoreTextComp->GetWidth() / 2.f, 12.f);
		pSinglePlayerScene.Add(p1ScoreGo);

		pHighScoreTitleGo = std::make_shared<GameObject>();
		pHighScoreTitleTextComp = pHighScoreTitleGo->AddComponent(new TextComponent("HIGH SCORE", arcadeFont, 255, 0, 0));
		pHighScoreTitleGo->SetPosition(screenWidth / 2.f - pHighScoreTitleTextComp->GetWidth() / 2.f, -4.f);
		pSinglePlayerScene.Add(pHighScoreTitleGo);

		pHighScoreGo = std::make_shared<GameObject>();
		pHighScoreTextComp = pHighScoreGo->AddComponent(new TextComponent(" 30000", arcadeFont, 255, 255, 255));
		pHighScoreGo->SetPosition(screenWidth / 2.f - pHighScoreTextComp->GetWidth() / 2.f, 12.f);
		pSinglePlayerScene.Add(pHighScoreGo);

		// Level
		auto pLevel1Go = std::make_shared<GameObject>();
		auto pLevel1Comp = pLevel1Go->AddComponent(new LevelComponent("../Data/Levels/level1.txt"));
		pSinglePlayerScene.Add(pLevel1Go);
		pLevel1Comp;

		// Round# Text
		auto pRoundGo = std::make_shared<GameObject>();
		auto pRoundTextComp = pRoundGo->AddComponent(new TextComponent("ROUND  1", arcadeFont, 255, 255, 255));
		auto pRoundTimedSetActiveComp = pRoundGo->AddComponent(new TimedSetActiveComponent(2.5f, false));
		pRoundGo->SetPosition(screenWidth / 2.f - pRoundTextComp->GetWidth() / 2.f, 208.f);
		pSinglePlayerScene.Add(pRoundGo);

		auto pReadyGo = std::make_shared<GameObject>();
		auto pReadyTextComp = pReadyGo->AddComponent(new TextComponent("READY !", arcadeFont, 255, 255, 255));
		auto pReadyTimedSetActiveComp = pReadyGo->AddComponent(new TimedSetActiveComponent(2.5f, false));
		pReadyGo->SetPosition(screenWidth / 2.f - pReadyTextComp->GetWidth() / 2.f, 240.f);
		pSinglePlayerScene.Add(pReadyGo);

		// Player Lives
		auto pPlayerLives = std::make_shared<GameObject>();
		auto pPlayerLivesComp = pPlayerLives->AddComponent(new PlayerLivesComponent(0, screenHeight - 16.f));
		pSinglePlayerScene.Add(pPlayerLives);

		// Player
		auto pPlayer = std::make_shared<GameObject>();
		auto pPlayerComp = pPlayer->AddComponent(new PlayerComponent(48.f, screenHeight - 80.f, 1));
		pPlayerComp->RegisterLevel(pLevel1Comp);
		pPlayerComp->AddObserver(pPlayerLivesComp);
		pSinglePlayerScene.Add(pPlayer);

		pPlayerLivesComp->SetSpriteId(pPlayerComp->GetSpriteId());
		pPlayerLivesComp->InitializeLives(pPlayerComp->GetLives());

		// Commands
		Command* pPlayerMoveLeft = new MovePlayerCommand(pPlayer.get(), -1.f, 0);
		input.AddControllerCommand(pSinglePlayerScene.GetId(), 0, ControllerButton::DPadLeft, PressType::HELD, pPlayerMoveLeft);

		Command* pPlayerMoveRight = new MovePlayerCommand(pPlayer.get(), 1.f, 0);
		input.AddControllerCommand(pSinglePlayerScene.GetId(), 0, ControllerButton::DPadRight, PressType::HELD, pPlayerMoveRight);

		Command* pPlayerMoveUp = new MovePlayerCommand(pPlayer.get(), 0, 1.f);
		input.AddControllerCommand(pSinglePlayerScene.GetId(), 0, ControllerButton::ButtonB, PressType::DOWN, pPlayerMoveUp);

		Command* pPlayerShootBubble = new ShootBubblePlayerCommand(pPlayer.get());
		input.AddControllerCommand(pSinglePlayerScene.GetId(), 0, ControllerButton::ButtonA, PressType::DOWN, pPlayerShootBubble);

		// Restart Function
		auto RestartSinglePlayer = [&soundSystem, pRoundTimedSetActiveComp, pReadyTimedSetActiveComp]()
		{
			soundSystem.PlayMusic(1, 1.f, -1);
			soundSystem.StopMusic(); //todo: remove
			pRoundTimedSetActiveComp->ResetTimer();
			pReadyTimedSetActiveComp->ResetTimer();

			std::cout << "restarted single player\n";
		};
		pSinglePlayerScene.SetRestartFunction(RestartSinglePlayer);

		//*******************************
		// Set Starting Scene to MainMenu
		//*******************************
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