#pragma once
#include <vector>
#define RAYLIB_CXX_STANDARD_MAIN
#include "raylib.h"

using std::vector;

class Grid {
public:
	Grid();
	void Initialize();	
	void Draw() const;
	[[nodiscard]] bool IsCellOutside(int row, int column) const;
	[[nodiscard]] bool isCellEmpty(int row, int column) const;
	int ClearFullRows();
	int grid[20][10]{};

private:
	[[nodiscard]] bool IsRowFull(int row) const;
	void ClearRow(int row);
	void MoveRowDown(int row, int numRows);
	int numRows;
	int numCols;
	int cellSize;
	vector<Color> colors;
};