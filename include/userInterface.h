#pragma once
#include <stdio.h>
#include "../include/game.h"
#include "../include/raylib.h"
#include "../include/colors.h"
#include "../include/game.h"

class UserInterface {
public:
	UserInterface(Game* gameInstance, Font gameFont);
	void DrawComponents();

private:
	void DrawBasicComponents();
	void DrawScoreComponent();
	void DrawBlocksComponent();
	void DrawUIElementTextAbove(Font font, const char* text, Rectangle rect, float fontSize, Color fontColor);
	void DrawUIElementTextMiddle(Font font, const char* text, Rectangle rect, float fontSize, Color fontColor);
	Font font;
	Game* game;
};