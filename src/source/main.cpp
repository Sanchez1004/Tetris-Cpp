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

#include <raylib.h>
#include <iostream>
#include "include/UserInterface.h"

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 620;

double lastUpdateTime = 0;

/**
 * Checks if the specified time interval has elapsed since the last update.
 *
 * @param interval double: The time interval in seconds.
 *
 * @return bool: True if the event is triggered, False otherwise.
 */
static bool EventTriggered(double interval) {
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval) {
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

int main() {
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris");
	SetTargetFPS(60);

	Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
	Game game = Game();
	UserInterface ui = UserInterface(&game, font);

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
