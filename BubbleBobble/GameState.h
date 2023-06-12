#pragma once
#include "Singleton.h"

namespace dae
{
	enum class GameMode : unsigned
	{
		SINGLEPLAYER,
		COOP,
		VERSUS
	};

	class GameState final : public Singleton<GameState>
	{
	public:
		void SetLevelId(int levelId) { m_LevelId = levelId; }

		void SetPlayer1Score(int score) { m_Player1Score = score; }
		void SetPlayer2Score(int score) { m_Player2Score = score; }

		void SetPlayer1Lives(int lives) { m_Player1Lives = lives; }
		void SetPlayer2Lives(int lives) { m_Player2Lives = lives; }

		void SetHighScore(int score) { m_HighScore = score; }
		void SetGameMode(GameMode gameMode) { m_GameMode = gameMode; }

		int GetLevelId() const { return m_LevelId; }

		int GetPlayer1Lives() const { return m_Player1Lives; }
		int GetPlayer2Lives() const { return m_Player2Lives; }

		int GetPlayer1Score() const { return m_Player1Score; }
		int GetPlayer2Score() const { return m_Player2Score; }

		int GetHighScore() const { return m_HighScore; }
		GameMode GetGameMode() const { return m_GameMode; }
	private:
		friend class Singleton<GameState>;
		GameState() = default;

		int m_LevelId{};

		int m_Player1Lives{};
		int m_Player2Lives{};

		int m_Player1Score{};
		int m_Player2Score{};

		int m_HighScore{};

		GameMode m_GameMode{ GameMode::SINGLEPLAYER };
	};
}