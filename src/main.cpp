#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>
#include "main.h"

const int WINDOW_WIDTH = 500;
const int WINDOWS_HEIGHT = 620;

double lastUpdateTime = 0;

bool EventTriggered(double interval) {
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval) {
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

void DrawUIElement(Font font, const char* text, Rectangle rect, int fontSize, Color color) {
	DrawRectangleRounded(rect, 0.3f, 6, lightPurple);
	DrawTextEx(font, text, { rect.x + 4, rect.y + 5 }, fontSize, 2, color);
}

int main() {
	InitWindow(500, 620, "Tetris");
	SetTargetFPS(60);

	Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
	Game game = Game();

	while (WindowShouldClose() == false) {
		UpdateMusicStream(game.music);
		game.HandleInput();

		if (EventTriggered(0.2)) {
			game.MoveBlockDown();
		}

		BeginDrawing();
		ClearBackground(darkPurple);

		//Next Block container
		DrawTextEx(font, "Next", { 365, 175 }, 38, 2, WHITE);
		DrawRectangleRounded({ 320, 215, 170, 180 }, 0.3f, 6, lightPurple);

		// Calling the method here, just before the next block container makes the next block
		// Appears on the container
		game.Draw();
		



		// Score container module
		DrawTextEx(font, "Score", { 360, 15 }, 38, 2, WHITE);
		DrawRectangleRounded({ 320, 55, 170, 60 }, 0.3f, 6, lightPurple);

		game.getScoreFontSize();

		char scoreText[10];
		sprintf_s(scoreText, "%d", game.score);
		Vector2 textSize = MeasureTextEx(font, scoreText, game.scoreFontSize, 2);

		DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2, 65}, game.scoreFontSize, 2, WHITE);
		if (game.maxScoreReached) {
			DrawTextEx(font, "MAX SCORE", { 335, 110 }, 30, 2, WHITE);
			DrawTextEx(font, "REACHED", { 349, 130 }, 30, 2, WHITE);
		}




		// Restart button creation
		Rectangle restartButton = { 316, 495, 178, 48 };
		DrawRectangleRounded({ restartButton }, 0.3f, 6, lightPurple);
		DrawTextEx(font, "RESTART[R]", { 320, 500 }, 34, 2, WHITE);

		// Pause button creation
		Rectangle pauseButton = { 316, 562, 178, 44 };
		DrawRectangleRounded({ pauseButton }, 0.3f, 6, lightPurple);
		DrawTextEx(font, "PAUSE[T]", { 340, 566 }, 34, 2, WHITE);
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
