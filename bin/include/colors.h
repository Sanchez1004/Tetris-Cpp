#pragma once

#include "raylib.h"
#include <vector>

using std::vector;

extern const Color darkGrey;
extern const Color green;
extern const Color red;
extern const Color orange;
extern const Color yellow;
extern const Color purple;
extern const Color cyan;
extern const Color blue;
extern const Color darkPurple;
extern const Color gameButtonlightPurple;
extern const Color gameButtonHoverlightPurple;

vector<Color> GetCellColors();