#include "UI.h"

UI::UI(Font gameFont) { font = gameFont; }


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

void UI::DrawUIElementTextAbove(Font font, const char* text, Rectangle rect, int fontSize, Color fontColor) {
	DrawRectangleRounded(rect, 0.3f, 6, lightPurple);

	Vector2 textSize = MeasureTextEx(font, text, fontSize, 2);
	float textX = rect.x + (rect.width - textSize.x) / 2;
	float textY = rect.y - textSize.y - 4;

	DrawTextEx(font, text, { textX, textY }, fontSize, 2, fontColor);
}

void UI::DrawUIElementTextMiddle(Font font, const char* text, Rectangle rect, int fontSize, Color fontColor) {
	DrawRectangleRounded(rect, 0.3f, 6, lightPurple);

	Vector2 textSize = MeasureTextEx(font, text, fontSize, 2);
	float textX = rect.x + (rect.width - textSize.x + 10) / 2;
	float textY = rect.y + (rect.height - textSize.y) / 2;

	DrawTextEx(font, text, { textX, textY }, fontSize, 2, fontColor);
}



void UI::DrawBasicElements() {
}