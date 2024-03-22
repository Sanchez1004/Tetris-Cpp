#include "game.h"
#include <random>

Game::Game() {
	grid = Grid();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gameOver = false;
	pause = false;
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
		pause = !pause;
		break;
	}
}

void Game::MoveBlockLeft() {
	if (!gameOver) {
		currentBlock.Move(0, -1);
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.Move(0, 1);
		}
	}
}

void Game::MoveBlockRigth() {
	if (!gameOver) {
		currentBlock.Move(0, 1);
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.Move(0, -1);
		}
	}
}

void Game::MoveBlockDown() {
	if (!gameOver && !pause) {
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
	grid.ClearFullRows();
}

void Game::RotateBlock() {
	if (!gameOver) {
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
	pause = false;
}
