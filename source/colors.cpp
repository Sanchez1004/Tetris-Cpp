#include "../include/colors.h"

const Color darkGrey = { 26, 31, 40, 255 };
const Color green = { 153, 255, 51, 255 };
const Color red = { 255, 102, 102, 255 };
const Color orange = { 255, 128, 0, 255 };
const Color yellow = { 255, 255, 102, 255 };
const Color purple = { 255, 153, 255, 255 };
const Color cyan = { 153, 255, 255, 255 };
const Color blue = { 102, 102, 255, 255 };
const Color lightPurple = { 100, 100, 130, 255 };
const Color darkPurple = { 70, 70, 90, 1 };

vector<Color> GetCellColors() {
	return{ darkGrey, green, red, orange, yellow, purple, cyan, blue };
}