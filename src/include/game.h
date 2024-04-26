#pragma once
#include "grid.h"
#include "source/blocks.cpp"
#include <map>
#include <random>

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
	bool gameOver;
	bool gamePaused;
	bool maxScoreReached;
	float scoreFontSize;
	float gameOverFontSize;
	int score;
	Music music;
	//UI ui;

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
	vector<Block> GetAllBlocks();
	vector<Block> blocks;
	Block GetRandomBlock();
	Block currentBlock;
	Block nextBlock;
	Grid grid;
	Sound rotateSound;
	Sound clearSound;
};