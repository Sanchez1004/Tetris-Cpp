#pragma once
#include "grid.h"
#include "../source/blocks.cpp"
#include "raylib.h"

enum GameState {
	GAME_PLAYING,
	GAME_PAUSED,
	GAME_OVER
};

using std::vector;

class Game {
public:
	Game();
	~Game();
	void Draw();
	void HandleInput();
	void OptionsMenu();
	void getScoreFontSize();
	void HandleDownBlockMove();
	void MoveBlockDown();
	[[nodiscard]] bool IsGameOver() const;
	[[nodiscard]] bool IsGamePaused() const;
	[[nodiscard]] bool IsGamePlaying() const;
	bool maxScoreReached;
	float scoreFontSize;
	float gameOverFontSize;
	int score;
	Music music{};
	Vector2 mousePosition;
	GameState gameState;

private:
	void TogglePause();
	void RotateBlock();	
	void MoveBlockLeft();
	void MoveBlockRigth();
	void LockBlock();
	void Reset();
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