/**
* === Suggestion: Use Singleton Pattern for Shared Game Instance ===
* To separate GUI logic from the main code and utilize methods from
* the main `Game` instance, consider implementing a Singleton pattern.
*
* This allows you to maintain a single global instance of "Game" accessible
* from both "main.cpp" and "UI.h".
*
* 1. Create a "GameManager" class responsible for managing the "Game" instance.
* 2. Access the "Game" instance through the "GameManager" in both places.
* 3. Ensure proper initialization and lifetime management.
*/
#include "raylib.h"
#include "../include/userInterface.h"
#include "../include/game.h"

constexpr int WINDOW_WIDTH = 500;
constexpr int WINDOW_HEIGHT = 620;

double lastUpdateTime = 0;

/**
 * Checks if the specified time interval has elapsed since the last update.
 *
 * @param interval double: The time interval in seconds.
 *
 * @return bool: True if the event is triggered, False otherwise.
 */
static bool EventTriggered(double interval) {
	const double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval) {
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}


int main() {
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris");
	SetTargetFPS(60);

	const Font font = LoadFontEx("Font/monogram.ttf", 64, nullptr, 0);

	/**
	 * @brief Instantiates a Game object using auto.
	 *
	 * This line instantiates a Game object using the auto keyword, allowing the compiler to deduce the type
	 * of the variable based on the type of the expression Game(). This improves code readability by avoiding
	 * redundant type declarations.
	 */
	auto game = Game();

	/**
	 * @brief Instantiates a UserInterface object using auto.
	 *
	 * This line instantiates a UserInterface object using the auto keyword, similarly allowing the compiler
	 * to deduce the type of the variable based on the type of the expression UserInterface(&game, font).
	 * Utilizing auto enhances code clarity by eliminating explicit type declarations.
	 */
	auto ui = UserInterface(&game, font);

	while (WindowShouldClose() == false) {
		UpdateMusicStream(game.music);
		game.HandleInput();

		if (EventTriggered(0.2)) {
			game.MoveBlockDown();
		}

		BeginDrawing();
		ClearBackground(darkPurple);

		ui.DrawComponents();

		EndDrawing();
	}

	CloseWindow();
}
