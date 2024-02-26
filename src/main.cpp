#include <raylib.h>
#include <iostream>
#include "grid.h"
#include "blocks.cpp"

int main() {
	InitWindow(300, 600, "Tetris");
	SetTargetFPS(60);
	Color bg = { 44, 44, 127, 255 };

	Grid grid = Grid();
	grid.Print();

	ZBlock block = ZBlock();
	block.Move(3, 4);

	while (WindowShouldClose() == false) {
		BeginDrawing();
		ClearBackground(bg);
		grid.Draw();
		block.Draw();

		EndDrawing();
	}

	CloseWindow();
}