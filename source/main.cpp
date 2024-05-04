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
 * @return bool: True if the event is triggered, False otherwise.
 */
static bool EventTriggered() {
	if (const double currentTime = GetTime(); currentTime - lastUpdateTime >= 0.2) {
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

int main() {
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris");
	SetExitKey(0);
	SetTargetFPS(60);

	const Font font = LoadFontEx("Font/monogram.ttf", 64, nullptr, 0);

	auto game = Game();
	const auto ui = UserInterface(&game, font);

	while (!game.GameShouldClose()) {
		game.HandleInput();
		BeginDrawing();
		ClearBackground(darkPurple);
		game.HandlePlayedMusic();

		switch (game.currentMenuState) {
			case MAIN_MENU:
				ui.DrawMenuInterface();
				break;

			case GAME:
				if (EventTriggered()) {
					game.MoveBlockDown();
				}
				ui.DrawGameInterface();
				break;

			case HIGH_SCORES:
				break;
			case MENU_SETTINGS:
				break;
			default:
				break;
		}
		EndDrawing();
	}
	CloseWindow();
}
