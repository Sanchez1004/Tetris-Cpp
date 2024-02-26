#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

using std::vector;

class Block {
public:
	Block();
	void Draw();
	void Move(int rows, int columns);
	vector<Position> GetCellPositions();
	int id;
	std::map <int, vector<Position>> cells;

private:
	int cellSize;
	int rotationState;
	vector<Color> colors;
	int rowOffSet;
	int columnOffSet;
};
