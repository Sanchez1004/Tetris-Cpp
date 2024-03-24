#include "game.h"
#include <random>

Game::Game() {
	grid = Grid();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gameOver = false;
	gamePaused = false;
	maxScoreReached = false;
	score = 0;
}

Block Game::GetRandomBlock() {
	if (blocks.empty()) {
		blocks = GetAllBlocks();
	}
	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	return block;
}

vector<Block> Game::GetAllBlocks() {
	return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

void Game::Draw() {
	grid.Draw();
	currentBlock.Draw();
}

void Game::HandleInput(){
	int keyPressed = GetKeyPressed();
	if (gameOver && keyPressed != 0) {
		gameOver = false;
		Reset();
	}
	switch (keyPressed)
	{
	// This kind of definition makes posible to handle both ARROWS and WASD to control the blocks
	case KEY_LEFT:
	case KEY_A:
		MoveBlockLeft();
		break;
	case KEY_RIGHT:
	case KEY_D:
		MoveBlockRigth();
		break;
	case KEY_DOWN:
	case KEY_S:
		MoveBlockDown();
		// If the game is paused the score will no update even if we press de W or DOWN key
		if (!gamePaused) {
			UpdateScore(0, 1);
		}
		break;
	case KEY_UP:
	case KEY_W:
		RotateBlock();
		break;
	case KEY_R:
		Reset();
		break;
	case KEY_T:
		// If pause = true -> false, if pause = false -> true
		gamePaused = !gamePaused;
		break;
	}
}

void Game::MoveBlockLeft() {
	if (!gameOver && !gamePaused) {
		currentBlock.Move(0, -1);
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.Move(0, 1);
		}
	}
}

void Game::MoveBlockRigth() {
	if (!gameOver && !gamePaused) {
		currentBlock.Move(0, 1);
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.Move(0, -1);
		}
	}
}

void Game::MoveBlockDown() {
	if (!gameOver && !gamePaused) {
		currentBlock.Move(1, 0);
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.Move(-1, 0);
			LockBlock();
		}
	}
}

void Game::LockBlock() {
	vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		grid.grid[item.row][item.column] = currentBlock.id;
	}
	currentBlock = nextBlock;
	if (BlockFits() == false) {
		gameOver = true;
	}
	nextBlock = GetRandomBlock();
	int rowsCleared = grid.ClearFullRows();
	UpdateScore(rowsCleared, 0);
}

void Game::RotateBlock() {
	if (!gameOver && !gamePaused) {
		currentBlock.Rotate();
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.UndoRotation();
		}
	}
}

bool Game::IsBlockOutside() {
	vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		if (grid.IsCellOutside(item.row, item.column)) {
			return true;
		}
	}
	return false;
}

bool Game::BlockFits() {
	vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		if (grid.isCellEmpty(item.row, item.column) == false) {
			return false;
		}
	}
	return true;
}

void Game::Reset() {
	grid.Initialize();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gamePaused = false;
	maxScoreReached = false;
	score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints) {
	switch (linesCleared) {
	case 1:
		score += 100;
		break;
	case 2:
		score += 300;
		break;
	case 3:
		score += 500;
		break;
	default:
		break;
	}
	if (score <= 999999998) {
		score += moveDownPoints;
	}
	if (score == 999999999) {
		maxScoreReached = true;
	}
}
