#pragma once
#include "grid.h"
#include "blocks.cpp"

using std::vector;

class Game {
public:
	Game();
	Block GetRandomBlock();
	vector<Block> GetAllBlocks();
	void Draw();
	void HandleInput();
	void MoveBlockLeft();
	void MoveBlockRigth();
	void MoveBlockDown();
	Grid grid;
	bool gameOver;
	bool pause;

private:
	void RotateBlock();	
	void LockBlock();
	void Reset();
	bool IsBlockOutside();
	bool BlockFits();
	vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
};