#pragma once
#include "grid.h"
#include "../source/blocks.cpp"
#include "raylib.h"

enum GameState {
	GAME_PLAYING,
	GAME_PAUSED,
	GAME_OVER
};

enum MenuState {
	MAIN_MENU,
	GAME,
	HIGH_SCORES,
	OPTIONS,
	EXIT
};

using std::vector;

class Game {
public:
	Game();
	~Game();
	void Reset();
	void DrawGridAndBlocks();
	void HandleInput();
	void OptionsMenu();
	void getScoreFontSize();
	void HandleDownBlockMove();
	void MoveBlockDown();
	[[nodiscard]] int getScore() const;
	[[nodiscard]] bool IsGameOver() const;
	[[nodiscard]] bool IsGamePaused() const;
	[[nodiscard]] bool IsGamePlaying() const;
	[[nodiscard]] bool GameShouldClose() const;
	bool maxScoreReached;
	float scoreFontSize;
	float gameOverFontSize;
	Music music{};
	Vector2 mousePosition;
	GameState gameState;
	MenuState currentMenuState;

private:
	int score;
	void TogglePause();
	void RotateBlock();
	void MoveBlockLeft();
	void MoveBlockRigth();
	void LockBlock();
	void UpdateScore(int linesCleared, int moveDownPoints);
	bool IsBlockOutside();
	bool BlockFits();
	static vector<Block> GetAllBlocks();
	vector<Block> blocks;
	Block GetRandomBlock();
	Block currentBlock;
	Block nextBlock;
	Grid grid;
	Sound rotateSound{};
	Sound clearSound{};
};