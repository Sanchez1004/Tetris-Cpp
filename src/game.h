#pragma once
#include "grid.h"
#include "blocks.cpp"

using std::vector;

class Game {
public:
	Game();
	~Game();
	void Draw();
	void HandleInput();
	void MoveBlockDown();
	void getScoreFontSize();
	bool gameOver;
	bool gamePaused;
	bool maxScoreReached;
	float scoreFontSize;
	float gameOverFontSize;
	int score;
	Music music;

private:
	void HandlePausedGameMusic();
	void RotateBlock();	
	void MoveBlockLeft(); 
	void MoveBlockRigth();
	void LockBlock();
	void Reset();
	void UpdateScore(int linesCleared, int moveDownPoints);
	bool IsBlockOutside();
	bool BlockFits();
	vector<Block> GetAllBlocks();
	vector<Block> blocks;
	Block GetRandomBlock();
	Block currentBlock;
	Block nextBlock;
	Grid grid;
	Sound rotateSound;
	Sound clearSound;
};