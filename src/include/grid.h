#pragma once
#include <vector>
#include <raylib.h>

using std::vector;

class Grid {
public:
	Grid();
	void Initialize();	
	void Draw();
	bool IsCellOutside(int row, int column);
	bool isCellEmpty(int row, int column);
	int ClearFullRows();
	int grid[20][10];

private:
	bool IsRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int numRows);
	int numRows;
	int numCols;
	int cellSize;
	vector<Color> colors;
};