#include "block.h"

Block::Block() {
	cellSize = 30;
	rotationState = 0;
	colors = GetCellColors();
	rowOffSet = 0;
	columnOffSet = 0;
}

void Block::Draw(int offsetX, int offsetY) {
	vector<Position> tiles = GetCellPositions();
	for (Position item : tiles) {
		DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize 
			+ offsetY, cellSize - 1, cellSize - 1, colors[id]);
	}
}

void Block::Move(int rows, int columns) {
	rowOffSet += rows;
	columnOffSet += columns;
}

void Block::Rotate() {
	rotationState++;
	if (rotationState == cells.size()) {
		rotationState = 0;
	}
}

void Block::UndoRotation() {
	rotationState--;
	if (rotationState == -1) {
		rotationState = cells.size() - 1;
	}
}

vector<Position> Block::GetCellPositions() {
	vector<Position> tiles = cells[rotationState];
	vector<Position> movedTiles;
	for (Position item : tiles) {
		Position newPosition = Position(item.row + rowOffSet, item.column + columnOffSet);
		movedTiles.push_back(newPosition);
	}
	return movedTiles;
}