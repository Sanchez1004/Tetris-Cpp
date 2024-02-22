#include <raylib.h>
#include <iostream>
#include "grid.h"

int main() {
	InitWindow(300, 600, "Tetris");
	SetTargetFPS(60);
	Color bg = { 44, 44, 127, 255 };

	Grid grid = Grid();
	grid.grid[0][0] = 1;
	grid.grid[1][0] = 4;
	grid.grid[0][2] = 7;

	grid.Print();

	while (WindowShouldClose() == false) {
		BeginDrawing();
		ClearBackground(bg);
		grid.Draw();

		EndDrawing();
	}

	CloseWindow();
}