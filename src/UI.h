#pragma once
#include "game.h"
#include "raylib.h"
#include "colors.h"
#include "game.h"

class UI{
public:
	UI(Font gameFont);
	void DrawBasicElements();
	void DrawUIElementTextAbove(Font font, const char* text, Rectangle rect, int fontSize, Color fontColor);
	void DrawUIElementTextMiddle(Font font, const char* text, Rectangle rect, int fontSize, Color fontColor);

private:
	Font font;
};