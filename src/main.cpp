#include <raylib.h>
#include "game.h"

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
	InitWindow(300, 600, "Tetris");
	SetTargetFPS(60);
	Color bg = { 44, 44, 127, 255 };

	Game game = Game();

	while (WindowShouldClose() == false) {
		game.HandleInput();

		if (EventTriggered(0.02)) {
			game.MoveBlockDown();
		}

		BeginDrawing();
		ClearBackground(bg);
		game.Draw();
		EndDrawing();
	}

	CloseWindow();
}