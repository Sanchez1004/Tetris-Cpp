#include <raylib.h>
#include "game.h"

int main() {
	InitWindow(300, 600, "Tetris");
	SetTargetFPS(60);
	Color bg = { 44, 44, 127, 255 };

	Game game = Game();

	while (WindowShouldClose() == false) {
		game.HandleInput();
		BeginDrawing();
		ClearBackground(bg);
		game.Draw();
		EndDrawing();
	}

	CloseWindow();
}