#include "../include/game.h"
#include <map>
#include <random>

constexpr int INITIAL_SCORE_FONT_SIZE = 38;
constexpr int INITIAL_GAME_OVER_FONT_SIZE = 32;

/**
 * @brief Constructs a new Game object.
 *
 * This constructor initializes the game grid, the list of all blocks, and the current and next blocks.
 * It also sets the initial game state and score, and loads the game audio.
 */
Game::Game():
	maxScoreReached(false),
	scoreFontSize(INITIAL_SCORE_FONT_SIZE),
	gameOverFontSize(INITIAL_GAME_OVER_FONT_SIZE),
	score(0),
	mousePosition(GetMousePosition()),
	gameState(GAME_PLAYING),
	currentMenuState(MAIN_MENU),
	blocks(GetAllBlocks()),
	currentBlock(GetRandomBlock()),
	nextBlock(GetRandomBlock()),
	grid(Grid())
{
	InitAudioDevice();  // Initialize the audio device
	music = LoadMusicStream("sounds/music.mp3");  // Load the game music
	PlayMusicStream(music);  // Start playing the game music
	rotateSound = LoadSound("Sounds/rotate.mp3");  // Load the sound for block rotation
	clearSound = LoadSound("Sounds/clear.mp3");  // Load the sound for clearing lines
}

Game::~Game() {
	UnloadMusicStream(music);
	UnloadSound(rotateSound);
	UnloadSound(clearSound);
	CloseAudioDevice();
}

/**
 * @brief Returns a random block from the available blocks.
 *
 * This method uses a random number generator to select a block at random from the list of available blocks.
 * If the list of blocks is empty, it is first replenished by calling the `GetAllBlocks` method.
 * After a block is selected, it is removed from the list to ensure that each block is selected only once per cycle.
 *
 * @return A randomly selected block.
 */
Block Game::GetRandomBlock() {
	// Initialize a random number generator
	static std::random_device rd;
	static std::mt19937 gen(rd());

	// If the list of blocks is empty, replenish it
	if (blocks.empty()) {
		blocks = GetAllBlocks();
	}

	// Generate a random index
	std::uniform_int_distribution<> dis(0, static_cast<int>(blocks.size()) - 1);
	const size_t randomIndex = dis(gen);

	// Select the block at the random index
	Block block = blocks[randomIndex];

	// Remove the selected block from the list
	blocks.erase(blocks.begin() + randomIndex); // NOLINT(*-narrowing-conversions)

	// Return the selected block
	return block;
}


vector<Block> Game::GetAllBlocks() {
	return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

void Game::Draw() {
	grid.Draw();
	currentBlock.Draw(11, 11);

	int x, y;
	switch (nextBlock.id) {
		case 3:
			x = 255; y = 290;
		break;
		case 4:
			x = 255; y = 270;
		break;
		default:
			x = 270; y = 270;
	}
	nextBlock.Draw(x, y);
}

bool Game::IsGameOver () const {
	return gameState == GAME_OVER;
}

bool Game::IsGamePaused () const {
	return gameState == GAME_PAUSED;
}

bool Game::IsGamePlaying () const {
	return gameState == GAME_PLAYING;
}

bool Game::GameShouldClose() const {
	return WindowShouldClose() || currentMenuState == EXIT;
}

/**
 * @brief Handles user input during the game.
 *
 * This method maps keyboard keys to corresponding game actions. When a key is pressed,
 * the corresponding game action is executed.
 *
 * The mapping is stored in a static map where the keys are the keyboard key codes and
 * the values are pointers to the member functions that implement the game actions.
 *
 * If the game is over and any key is pressed, the game is reset.
 */
void Game::HandleInput() {
	static const std::map<int, void(Game::*)()> keyHandlers = {
		{KEY_LEFT, &Game::MoveBlockLeft},  // Move the block left when the LEFT key or 'A' is pressed
		{KEY_A, &Game::MoveBlockLeft},
		{KEY_RIGHT, &Game::MoveBlockRigth},  // Move the block right when the RIGHT key or 'D' is pressed
		{KEY_D, &Game::MoveBlockRigth},
		{KEY_DOWN, &Game::HandleDownBlockMove},  // Move the block down when the DOWN key or 'S' is pressed
		{KEY_S, &Game::HandleDownBlockMove},
		{KEY_UP, &Game::RotateBlock},  // Rotate the block when the UP key or 'W' is pressed
		{KEY_W, &Game::RotateBlock},
		{KEY_R, &Game::Reset},  // Reset the game when the 'R' key is pressed
		{KEY_T, &Game::TogglePause},  // Toggle pause when the 'T' key is pressed
		{KEY_ESCAPE, &Game::OptionsMenu}
	};

	mousePosition = GetMousePosition();

	const int keyPressed = GetKeyPressed();  // Get the key pressed by the user
	if (IsGameOver() && keyPressed != 0) {
		gameState = GAME_PLAYING;
		Reset();
	}

	if (keyHandlers.count(keyPressed) > 0) {
		(this->*keyHandlers.at(keyPressed))();  // Execute the game action corresponding to the key pressed
	}
}

void Game::OptionsMenu() {
	currentMenuState = EXIT;
}

void Game::HandleDownBlockMove() {
	MoveBlockDown();
	UpdateScore(0, 1);
}

void Game::TogglePause() {
	if (IsGamePlaying()) {
		PauseMusicStream(music);
		gameState = GAME_PAUSED;
	}
	else if (IsGamePaused()) {
		ResumeMusicStream(music);
		gameState = GAME_PLAYING;
	}
}

void Game::MoveBlockLeft() {
	if (IsGamePlaying()) {
		currentBlock.Move(0, -1);
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.Move(0, 1);
		}
	}
}

void Game::MoveBlockRigth() {
	if (IsGamePlaying()) {
		currentBlock.Move(0, 1);
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.Move(0, -1);
		}
	}
}

void Game::MoveBlockDown() {
	if (IsGamePlaying()) {
		currentBlock.Move(1, 0);
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.Move(-1, 0);
			LockBlock();
		}
	}
}

void Game::LockBlock() {
	vector<Position> tiles = currentBlock.GetCellPositions();
	for (const Position item : tiles) {
		grid.grid[item.row][item.column] = currentBlock.id;
	}
	currentBlock = nextBlock;
	if (BlockFits() == false) {
		gameState = GAME_OVER;
		StopMusicStream(music);
	}
	nextBlock = GetRandomBlock();
	if (const int rowsCleared = grid.ClearFullRows(); rowsCleared > 0) {
		PlaySound(clearSound);
		UpdateScore(rowsCleared, 0);
	}
}

/**
 * @brief Adjusts the font size of the score and game over text based on the current score.
 *
 * This method calculates the number of digits in the current score. If the number of digits is 7 or more,
 * it reduces the font size of the score and game over text proportionally to the number of digits.
 * Otherwise, it sets the font size to their initial values.
 */
void Game::getScoreFontSize() {
	if (const int digits = static_cast<int>(floor(log10(score))) + 1; digits >= 7) {
		const auto floatDigits = static_cast<float>(digits);
		scoreFontSize = 40.0f - floatDigits;
		gameOverFontSize = 34.0f - floatDigits;
	}
	else {
		scoreFontSize = INITIAL_SCORE_FONT_SIZE;
		gameOverFontSize = INITIAL_GAME_OVER_FONT_SIZE;
	}
}

int Game::getScore() {
	return score;
}

void Game::RotateBlock() {
	if (IsGamePlaying()) {
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
	for (const Position item: tiles) {  // NOLINT(*-use-anyofallof)
		if (grid.IsCellOutside(item.row, item.column)) {
			return true;
		}
	}
	return false;
}

bool Game::BlockFits() {
	vector<Position> tiles = currentBlock.GetCellPositions();
	for (const Position item : tiles) { // NOLINT(*-use-anyofallof)
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
	maxScoreReached = false;
	score = 0;
	StopMusicStream(music);
	PlayMusicStream(music); // This will play the music again
	gameState = GAME_PLAYING;
}


/**
 * @brief Updates the game score based on the lines cleared and points earned from moving down.
 *
 * This method updates the score of the game. It adds points to the score based on the number of lines cleared.
 * The points for clearing 1, 2, or 3 lines are 100, 300, and 500 respectively. It also adds points earned from moving down.
 * If adding the move down points would cause the score to exceed 999999998, it sets the score to 999999999 and sets maxScoreReached to true.
 *
 * @param linesCleared The number of lines cleared in the game.
 * @param moveDownPoints The points earned from moving down.
 */
void Game::UpdateScore(const int linesCleared, const int moveDownPoints) {
	static const std::map<int, int> pointsPerLine = { {1, 100}, {2, 300}, {3, 500} };

	if (pointsPerLine.count(linesCleared) > 0) {
		score += pointsPerLine.at(linesCleared);
	}

	if (score <= 999999998 - moveDownPoints) {
		score += moveDownPoints;
	}
	else if (!maxScoreReached) {
		score = 999999999;
		maxScoreReached = true;
	}
}
