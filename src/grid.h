#pragma once
#include <vector>
#include <raylib.h>

using std::vector;

class Grid {
public:
	Grid();
	void Initialize();	
	void Print();
	void Draw();

	int grid[20][10];

private:
	int numRows;
	int numCols;
	int cellSize;
	vector<Color> colors;
};