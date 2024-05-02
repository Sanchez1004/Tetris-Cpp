#pragma once
#include "../include/game.h"
#include "raylib.h"

class UserInterface {
public:
	UserInterface(Game* gameInstance, const Font &gameFont);
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