#include <raylib.h>
#include "game.h"
#include "colors.h"

double lastUpdateTime = 0;

bool EventTriggered(double interval) {
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval) {
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

int main() {
	InitWindow(500, 620, "Tetris");
	SetTargetFPS(60);

	Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
	Game game = Game();

	while (WindowShouldClose() == false) {
		game.HandleInput();

		if (EventTriggered(0.2)) {
			game.MoveBlockDown();
		}

		BeginDrawing();
		ClearBackground(darkBlue);
		DrawTextEx(font, "Score", { 360, 15 }, 38, 2, WHITE);
		DrawTextEx(font, "Next", { 365, 175 }, 38, 2, WHITE);
		DrawRectangleRounded({ 320, 55, 170, 60 }, 0.3, 6, lightBlue);
		DrawRectangleRounded({ 320, 215, 170, 180 }, 0.3, 6, lightBlue);

		// Restart button creation
		Rectangle restartButton = { 316, 495, 178, 48 };
		DrawRectangleRounded({ restartButton }, 0.3, 6, lightBlue);
		DrawTextEx(font, "RESTART(R)", { 320, 500 }, 34, 2, WHITE);

		// Pause button creation
		Rectangle pauseButton = { 316, 562, 178, 44 };
		DrawRectangleRounded({ pauseButton }, 0.3, 6, lightBlue);
		DrawTextEx(font, "PAUSE(T)", { 340, 566 }, 34, 2, WHITE);


		game.Draw();
		EndDrawing();
	}

	CloseWindow();
}