#include "../include/UserInterface.h"
#include "../include/colors.h"
#include "../include/game.h"
#include <cstdio>
#include <string>

/**
 * @brief Constructs a new UserInterface object.
 *
 * This constructor initializes the UserInterface object with a game instance and a font.
 * The game instance and font are used to draw the user interface elements and the game state.
 *
 * @param gameInstance A pointer to the Game object. This is the game instance for which the UI is being created.
 * @param gameFont The font to be used for drawing text in the UI.
 */
UserInterface::UserInterface(Game* gameInstance, const Font &gameFont) : font(gameFont), game(gameInstance) { }

void UserInterface::DrawComponents() const {
	DrawBlocksComponent();
	DrawBasicComponents();
	DrawScoreComponent();
}

void UserInterface::DrawUIElementTextAbove(const Font &font, const char *text, const Rectangle rect,
									       // ReSharper disable once CppDFAConstantParameter
                                           const float fontSize,
                                           const Color fontColor) {

	DrawRectangleRounded(rect, 0.3f, 6, lightPurple);

	const auto [xElementPosition, yElementPosition] = MeasureTextEx(font, text, fontSize, 2.0f);
	const float textX = rect.x + (rect.width - xElementPosition) / 2;
	const float textY = rect.y - yElementPosition - 4;

	DrawTextEx(font, text, { textX, textY }, fontSize, 2, fontColor);
}

void UserInterface::DrawUIElementTextMiddle(const Font &font, const char *text, const Rectangle rect,
                                            // ReSharper disable once CppDFAConstantParameter
                                            const float fontSize, const Color fontColor) {

	DrawRectangleRounded(rect, 0.3f, 6, lightPurple);

	const auto [xElementPosition, yElementPosition] = MeasureTextEx(font, text, fontSize, 2.0f);
	const float textX = rect.x + (rect.width - xElementPosition + 10) / 2;
	const float textY = rect.y + (rect.height - yElementPosition) / 2;

	DrawTextEx(font, text, { textX, textY }, fontSize, 2, fontColor);
}

void UserInterface::DrawBasicComponents() const {
	DrawUIElementTextMiddle(font, "RESTART(R)", { 315, 562, 180, 48 }, 34.0f, WHITE);
	DrawUIElementTextMiddle(font, "OPTIONS(O)", { 315, 460, 180, 48 }, 34.0f, WHITE);

	DrawUIElementTextMiddle(font, "PAUSE(T)", { 315, 511, 180, 48 }, 34.0f, WHITE);
	if (game->IsGamePaused()) {
		DrawTextEx(font, "GAME PAUSED\n\nPRESS[T]\n\nTO CONTINUE", { 64,220 }, 34, 2, WHITE);
	}
}

void UserInterface::DrawScoreComponent() const {
	DrawUIElementTextAbove(font, "Score", { 320, 55, 170, 60 }, 38, WHITE);

	game->getScoreFontSize();

	char scoreText[10];
	snprintf(scoreText, sizeof(scoreText), "%d", game->getScore());
	const auto [xScorePosition, yScorePosition] = MeasureTextEx(font, scoreText, game->scoreFontSize, 2);

	DrawTextEx(font, scoreText, { 320 + (170 - xScorePosition) / 2, 65 }, game->scoreFontSize, 2, WHITE);
	if (game->maxScoreReached) {
		DrawTextEx(font, "MAX SCORE", { 335, 110 }, 30, 2, WHITE);
		DrawTextEx(font, "REACHED", { 349, 130 }, 30, 2, WHITE);
	}

	// Display "GAME OVER" when the gama ends
	if (game->IsGameOver()) {
		const std::string totalScoreMessage = std::string("TOTAL SCORE: ") + scoreText;

		/*  This helps to get the size of the "totalScoreMessage" and automatically get moved
			the most center position
		*/
		const auto [x, y] = MeasureTextEx(font, totalScoreMessage.c_str(), game->gameOverFontSize, 0.5);
		DrawTextEx(font, "GAME OVER", { 86,220 }, 34, 0.5, WHITE);
		DrawTextEx(font, totalScoreMessage.c_str(), { (320 - x) / 2, 245 }, game->gameOverFontSize, 0.5, WHITE);
		DrawTextEx(font, "PREES ANY KEY", { 47,300 }, 34, 0.5, WHITE);
		DrawTextEx(font, "TO PLAY AGAIN", { 47,325 }, 34, 0.5, WHITE);
	}
}

void UserInterface::DrawBlocksComponent() const {
	DrawUIElementTextAbove(font, "Next", { 320, 215, 170, 180 }, 38, WHITE);

	// Calling the method here, just before the next block container makes the next block
	// Appears on the container
	game->Draw();
}


void UserInterface::DrawMenu() {

}

void UserInterface::DrawGame() {
	
}

void UserInterface::DrawHighScores() {

}

void UserInterface::DrawMenuStartButton() {

}

void UserInterface::DrawMenuHighScoresButtons() {

}

void UserInterface::DrawMenuExitButton() {

}