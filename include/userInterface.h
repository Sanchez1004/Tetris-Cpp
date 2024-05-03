#pragma once
#include "../include/game.h"

#include "raylib.h"

class UserInterface {
public:
	UserInterface(Game* gameInstance, const Font &gameFont);
	void DrawMenuInterface();
	void DrawGameInterface();
	void DrawHighScoresInterface();

private:
	void DrawGameRestartButton() const;

	void DrawGameOptionsButton() const;

	void DrawGameScoreComponent() const;
	void DrawGameBlocksComponent() const;
	void DrawMenuStartButton();
	void DrawMenuHighScoresButtons();
	void DrawMenuExitButton();

	static void DrawGameTextBoxAbove(const Font &font, const char* text, Rectangle rect, float fontSize, Color fontColor);
	static void DrawGameTextBoxMiddle(const Font &font, const char *text, Rectangle rect, float fontSize, Color fontColor);

	Font font;
	Game* game;
};
