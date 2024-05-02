#pragma once
#include "../include/game.h"
#include "raylib.h"

class UserInterface {
public:
	UserInterface(Game* gameInstance, const Font &gameFont);
	void DrawComponents() const;
	void DrawMenu();
	void DrawGame();
	void DrawHighScores();


private:
	void DrawBasicComponents() const;
	void DrawScoreComponent() const;
	void DrawBlocksComponent() const;
	void DrawMenuStartButton();
	void DrawMenuHighScoresButtons();
	void DrawMenuExitButton();

	static void DrawUIElementTextAbove(const Font &font, const char* text, Rectangle rect, float fontSize, Color fontColor);
	static void DrawUIElementTextMiddle(const Font &font, const char *text, Rectangle rect, float fontSize, Color fontColor);

	Font font;
	Game* game;
};