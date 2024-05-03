#include <utility>

#include "../include/button.h"

Button::Button(const Rectangle bounds, std::string text) : bounds(bounds), text(std::move(text)), isHovered(false),
                                                           isClicked(false) {}


void Button::UpdateButtonState(const Vector2 mousePosition) {
    isHovered = CheckCollisionPointRec(mousePosition, bounds);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)&& isHovered) {
        isClicked = true;
    }
}

void Button::DrawButton(const Font &font, const Color fontColor, const float fontSize, const Color buttonColor,
                        const Color hoverButtonColor) const {
    DrawRectangleRounded(bounds, 0.3f, 6, isHovered ? hoverButtonColor : buttonColor);

    // Center the text
    const Vector2 center = {bounds.x + bounds.width / 2.0f, bounds.y + bounds.height / 2.0f};
    const auto [x, y] = MeasureTextEx(font, text.c_str(), fontSize, 1.5f);
    const Vector2 textPosition = {center.x - x / 2.0f, center.y - y / 2.0f};

    DrawTextEx(font, text.c_str(), textPosition, fontSize, 1.5f, fontColor);
}