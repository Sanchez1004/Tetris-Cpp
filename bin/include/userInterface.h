#pragma once
#include <button.h>

#include "../include/game.h"

#include "raylib.h"

class UserInterface {
public:
	UserInterface(Game* gameInstance, const Font &gameFont);
	void DrawMenuInterface() const;
	void DrawGameInterface() const;
	void DrawHighScoresInterface() const;

private:
	void DrawGameRestartButton() const;
	void DrawGameOptionsButton() const;
	void DrawGameScoreComponent() const;
	void DrawGameBlocksComponent() const;
	void DrawMenuStartButton() const;
	void DrawMenuHighScoresButtons() const;
	void DrawMenuExitButton() const;
	void DrawMenuUserButton() const;
	void DrawMenuSettingsButton() const;
	static void DrawGameTextBoxAbove(const Font &font, const char* text, Rectangle rect, float fontSize, Color fontColor);
	static void DrawGameTextBoxMiddle(const Font &font, const char *text, Rectangle rect, float fontSize, Color fontColor);
	static Vector2 GetCenteredPositionComparedWindow(float xPosition, float yPosition);

	[[nodiscard]] Button CreateMenuCenteredButton(float xPosition, float yPosition, const std::string &text) const;
	[[nodiscard]] bool DrawExitConfirmation() const;

	Font font;
	Game* game;
};
