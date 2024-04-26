#pragma once
#include <vector>
#include "../include/raylib.h"

using std::vector;

class Grid {
public:
	Grid();
	void Initialize();	
	void Draw() const;
	bool IsCellOutside(int row, int column) const;
	bool isCellEmpty(int row, int column) const;
	int ClearFullRows();
	int grid[20][10]{};

private:
	bool IsRowFull(int row) const;
	void ClearRow(int row);
	void MoveRowDown(int row, int numRows);
	int numRows;
	int numCols;
	int cellSize;
	vector<Color> colors;
};