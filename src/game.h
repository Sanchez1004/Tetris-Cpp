#pragma once
#include "grid.h"
#include "blocks.cpp"

using std::vector;

class Game {
public:
	Game();
	Block GetRandomBlock();
	vector<Block> GetAllBlocks();
	Grid grid;
	void Draw();
	void HandleInput();
	void MoveBlockLeft();
	void MoveBlockRigth();
	void MoveBlockDown();
	bool gameOver;
	bool gamePaused;
	bool maxScoreReached;
	int score;

private:
	void RotateBlock();	
	void LockBlock();
	void Reset();
	void UpdateScore(int linesCleared, int moveDownPoints);
	bool IsBlockOutside();
	bool BlockFits();
	vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
};