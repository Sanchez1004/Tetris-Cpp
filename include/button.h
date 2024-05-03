#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "raylib.h"

class Button {
public:
    Rectangle bounds;
    std::string text;
    bool isHovered;
    bool isClicked;

    Button(Rectangle bounds, std::string text);

    void UpdateButtonState(Vector2 mousePosition);
    void DrawButton(const Font &font, Color fontColor, float fontSize, Color buttonColor, Color hoverButtonColor) const;
};

#endif //BUTTON_H
