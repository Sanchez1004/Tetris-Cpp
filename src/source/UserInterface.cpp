#include "include/UserInterface.h"

/**
 * @brief Constructs a new UserInterface object.
 *
 * This constructor initializes the UserInterface object with a game instance and a font.
 * The game instance and font are used to draw the user interface elements and the game state.
 *
 * @param gameInstance A pointer to the Game object. This is the game instance for which the UI is being created.
 * @param gameFont The font to be used for drawing text in the UI.
 */
UserInterface::UserInterface(Game* gameInstance, Font gameFont) : game(gameInstance), font(gameFont) { }



/**
 * @brief This method is responsible for drawing all the components of the User Interface (UI).
 *
 * The method calls three other methods in sequence:
 * 1. `DrawBlocksComponent()`: This method is responsible for drawing the blocks component of the UI.
 * 2. `DrawBasicComponents()`: This method is responsible for drawing the basic components of the UI such as buttons and labels.
 * 3. `DrawScoreComponent()`: This method is responsible for drawing the score component of the UI.
 *
 */
void UserInterface::DrawComponents() {
	DrawBlocksComponent();
	DrawBasicComponents();
	DrawScoreComponent();
}




/**
 * Draws a UI element with centered text inside a rounded rectangle.
 *
 * @param font Font: The font to use for the text.
 * @param text const char*: The text to display.
 * @param rect Rectangle: The rectangle defining the UI element's position and size.
 * @param fontSize int: The font size for the text.
 * @param fontColor Color: The color of the text.
 *
 */

void UserInterface::DrawUIElementTextAbove(Font font, const char* text, Rectangle rect, float fontSize, Color fontColor) {
	DrawRectangleRounded(rect, 0.3f, 6, lightPurple);

	Vector2 textSize = MeasureTextEx(font, text, fontSize, 2.0f);
	float textX = rect.x + (rect.width - textSize.x) / 2;
	float textY = rect.y - textSize.y - 4;

	DrawTextEx(font, text, { textX, textY }, fontSize, 2, fontColor);
}

void UserInterface::DrawUIElementTextMiddle(Font font, const char* text, Rectangle rect, float fontSize, Color fontColor) {
	DrawRectangleRounded(rect, 0.3f, 6, lightPurple);

	Vector2 textSize = MeasureTextEx(font, text, fontSize, 2.0f);
	float textX = rect.x + (rect.width - textSize.x + 10) / 2;
	float textY = rect.y + (rect.height - textSize.y) / 2;

	DrawTextEx(font, text, { textX, textY }, fontSize, 2, fontColor);
}




/**
 * @brief This method is responsible for drawing the basic components of the User Interface (UI).
 *
 * The method performs the following tasks:
 * 1. Draws a UI element with the text "RESTART(R)" at the specified position and size.
 * 2. Draws a UI element with the text "OPTIONS(O)" at the specified position and size.
 * 3. Draws a UI element with the text "PAUSE(T)" at the specified position and size.
 * 4. If the game is paused and not over:
 *    - Displays "GAME PAUSED\nPRESS[T]\nTO CONTINUE" at the specified position.
 *
 * @note This method is called every frame in the game loop to continuously update the basic components of the UI.
 */
void UserInterface::DrawBasicComponents() {
	DrawUIElementTextMiddle(font, "RESTART(R)", { 315, 562, 180, 48 }, 34.0f, WHITE);
	DrawUIElementTextMiddle(font, "OPTIONS(O)", { 315, 460, 180, 48 }, 34.0f, WHITE);

	DrawUIElementTextMiddle(font, "PAUSE(T)", { 315, 511, 180, 48 }, 34.0f, WHITE);
	if (game->gamePaused == true && !game->gameOver) {
		DrawTextEx(font, "GAME PAUSED\nPRESS[T]\nTO CONTINUE", { 64,220 }, 34, 2, WHITE);
	}
}






/**
 * @brief This method is responsible for drawing the score component of the User Interface (UI).
 *
 * The method performs the following tasks:
 * 1. Draws a UI element with the text "Score" at the specified position and size.
 * 2. Retrieves the font size for the score from the game instance.
 * 3. Converts the current score to a string and measures its size.
 * 4. Draws the current score at the center of the UI element.
 * 5. If the maximum score has been reached, it displays "MAX SCORE" and "REACHED" at the specified positions.
 * 6. If the game is over:
 *    - It constructs a string with the total score and measures its size.
 *    - Displays "GAME OVER" at the specified position.
 *    - Displays the total score at the center of the UI element.
 *    - Displays "PRESS ANY KEY" and "TO PLAY AGAIN" at the specified positions.
 *
 */
void UserInterface::DrawScoreComponent() {
	DrawUIElementTextAbove(font, "Score", { 320, 55, 170, 60 }, 38, WHITE);

	game->getScoreFontSize();

	char scoreText[10];
	sprintf_s(scoreText, "%d", game->score);
	Vector2 textSize = MeasureTextEx(font, scoreText, game->scoreFontSize, 2);

	DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2, 65 }, game->scoreFontSize, 2, WHITE);
	if (game->maxScoreReached) {
		DrawTextEx(font, "MAX SCORE", { 335, 110 }, 30, 2, WHITE);
		DrawTextEx(font, "REACHED", { 349, 130 }, 30, 2, WHITE);
	}

	// Display "GAME OVER" when the gama ends
	if (game->gameOver) {
		std::string totalScoreMessage = std::string("TOTAL SCORE: ") + scoreText;

		/*  This helps to get the size of the "totalScoreMessage" and automatically get moved
			the most center position
		*/
		Vector2 totalScoreMessageSize = MeasureTextEx(font, totalScoreMessage.c_str(), game->gameOverFontSize, 0.5);
		DrawTextEx(font, "GAME OVER", { 86,220 }, 34, 0.5, WHITE);
		DrawTextEx(font, totalScoreMessage.c_str(), { (320 - totalScoreMessageSize.x) / 2, 245 }, game->gameOverFontSize, 0.5, WHITE);
		DrawTextEx(font, "PREES ANY KEY", { 47,300 }, 34, 0.5, WHITE);
		DrawTextEx(font, "TO PLAY AGAIN", { 47,325 }, 34, 0.5, WHITE);
	}
}






/**
 * @brief This method is responsible for drawing the blocks component of the User Interface (UI).
 *
 * The method performs the following tasks:
 * 1. Draws a UI element with the text "Next" at the specified position and size.
 * 2. Calls the `Draw` method of the `game` instance.
 *
 * The `Draw` method is called just before the next block container is drawn, which ensures that the next block appears on the container.
 *
 */
void UserInterface::DrawBlocksComponent() {
	DrawUIElementTextAbove(font, "Next", { 320, 215, 170, 180 }, 38, WHITE);

	// Calling the method here, just before the next block container makes the next block
	// Appears on the container
	game->Draw();
}
