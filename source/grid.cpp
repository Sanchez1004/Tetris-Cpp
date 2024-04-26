#include "../include/grid.h"
#include "../include/colors.h"

Grid::Grid() {
	numRows = 20;
	numCols = 10;
	cellSize = 30;
	Initialize();
	colors = GetCellColors();
}

void Grid::Initialize() {
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			grid[row][col] = 0;
		}
	}
}
 
void Grid::Draw() const {
	for (int row = 0; row < numRows; row++) {
		for (int col = 0 ; col < numCols; col++) {
			const int cellValue = grid[row][col];
			DrawRectangle(col * cellSize + 11, row * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellValue]);
		}
	}
}

bool Grid::IsCellOutside(const int row, const int column) const {
	if (row >= 0 && row < numRows && column >= 0 && column < numCols) {
		return false;
	}
	return true;
}

bool Grid::isCellEmpty(const int row, const int column) const {
	if (grid[row][column] == 0) {
		return true;
	}
	return false;
}

int Grid::ClearFullRows() {
	int completed = 0;
	for(int row = numRows - 1; row >= 0; row--) {
		if (IsRowFull(row)) {
			ClearRow(row);
			completed++;
		}
		else if (completed > 0) {
			MoveRowDown(row, completed);
		}
	}
	return completed;
}

bool Grid::IsRowFull(const int row) const {
	for (int column = 0; column < numCols; column++) {
		if (grid[row][column] == 0) {
			return false;
		}
	}
	return true;
}

void Grid::ClearRow(const int row) {
	for (int column = 0; column < numCols; column++) {
		grid[row][column] = 0;
	}
}

void Grid::MoveRowDown(const int row, const int numRows) {
	for (int column = 0; column < numCols; column++) {
		grid[row + numRows][column] = grid[row][column];
		grid[row][column] = 0;
	}
}
