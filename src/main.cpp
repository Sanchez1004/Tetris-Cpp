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
#include "UI.h"

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
	UI ui = UI(font);

	while (WindowShouldClose() == false) {
		UpdateMusicStream(game.music);
		game.HandleInput();

		if (EventTriggered(0.2)) {
			game.MoveBlockDown();
		}

		BeginDrawing();
		ClearBackground(darkPurple);

		//Next Block container
		ui.DrawUIElementTextAbove(font, "Next", { 320, 215, 170, 180 }, 38, WHITE);
		// Calling the method here, just before the next block container makes the next block
		// Appears on the container
		game.Draw();
		
		
		// Score container 
		ui.DrawUIElementTextAbove(font, "Score", { 320, 55, 170, 60 }, 38, WHITE);

		game.getScoreFontSize();

		char scoreText[10];
		sprintf_s(scoreText, "%d", game.score);
		Vector2 textSize = MeasureTextEx(font, scoreText, game.scoreFontSize, 2);

		DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2, 65}, game.scoreFontSize, 2, WHITE);
		if (game.maxScoreReached) {
			DrawTextEx(font, "MAX SCORE", { 335, 110 }, 30, 2, WHITE);
			DrawTextEx(font, "REACHED", { 349, 130 }, 30, 2, WHITE);
		}

		ui.DrawBasicElements();
			
		if (game.gamePaused == true && !game.gameOver) {
			DrawTextEx(font, "GAME PAUSED\nPRESS[T]\nTO CONTINUE", { 64,220 }, 34, 2, WHITE);
		}

		// Display "GAME OVER" when the gama ends
		if (game.gameOver) {
			std::string totalScoreMessage = std::string("TOTAL SCORE: ") + scoreText;

			/*  This helps to get the size of the "totalScoreMessage" and automatically get moved
				the most center position 
			*/
			Vector2 totalScoreMessageSize = MeasureTextEx(font, totalScoreMessage.c_str(), game.gameOverFontSize, 0.5);
			DrawTextEx(font, "GAME OVER", {86,220}, 34, 0.5, WHITE);
			DrawTextEx(font, totalScoreMessage.c_str(), { (320 - totalScoreMessageSize.x) / 2, 245}, game.gameOverFontSize, 0.5, WHITE);
			DrawTextEx(font, "PREES ANY KEY", { 47,300 }, 34, 0.5, WHITE);
			DrawTextEx(font, "TO PLAY AGAIN", { 47,325 }, 34, 0.5, WHITE);
		}
		EndDrawing();
	}

	CloseWindow();
}
