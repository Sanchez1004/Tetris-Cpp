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
	scoreFontSize = 38;
	gameOverFontSize = 32;
	InitAudioDevice();
	music = LoadMusicStream("sounds/music.mp3");
	PlayMusicStream(music);
	rotateSound = LoadSound("Sounds/rotate.mp3");
	clearSound = LoadSound("Sounds/clear.mp3");
}

Game::~Game() {
	UnloadMusicStream(music);
	UnloadSound(rotateSound);
	UnloadSound(clearSound);
	CloseAudioDevice();
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
	currentBlock.Draw(11, 11);
	switch (nextBlock.id) {
	case 3:
		nextBlock.Draw(255, 290);
		break;
	case 4:
		nextBlock.Draw(255, 270);
		break;
	default:
		nextBlock.Draw(270, 270);
	}
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
		StopMusicStream(music);
		Reset();
		break;
	case KEY_T:
		// If pause = true -> false, if pause = false -> true
		HandlePausedGameMusic();
		gamePaused = !gamePaused;
		break;
	}
}

void Game::HandlePausedGameMusic() {
	if (!gamePaused) {
		PauseMusicStream(music);
	}
	else {
		ResumeMusicStream(music);
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
		StopMusicStream(music);
	}
	nextBlock = GetRandomBlock();
	int rowsCleared = grid.ClearFullRows();
	if (rowsCleared > 0) {
		PlaySound(clearSound);
		UpdateScore(rowsCleared, 0);
	}
}

void Game::getScoreFontSize() {
	int digits = floor(log10(score)) + 1;
	switch (digits) {
	case 7:
		scoreFontSize = 36;
		gameOverFontSize = 30;
		break;
	case 8:
		scoreFontSize = 34;
		gameOverFontSize = 28;
		break;
	case 9:
		scoreFontSize = 32;
		gameOverFontSize = 26;
		break;
	default:
		scoreFontSize = 38;
		gameOverFontSize = 32;
	}
}

void Game::RotateBlock() {
	if (!gameOver && !gamePaused) {
		currentBlock.Rotate();
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.UndoRotation();
		}
		else { // When the block rotates it play this sound
			PlaySound(rotateSound); 
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
	PlayMusicStream(music); // This will play the music again, becuse in the LockBlock() method it
}							// Stop was stopped

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
