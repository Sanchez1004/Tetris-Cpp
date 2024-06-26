#include "../include/UserInterface.h"
#include <cstdio>
#include <string>
#include "../include/button.h"
#include "../include/colors.h"
#include "../include/game.h"

/**
 * @brief Constructs a new UserInterface object.
 *
 * This constructor initializes the UserInterface object with a game instance and a font.
 * The game instance and font are used to draw the user interface elements and the game state.
 *
 * @param gameInstance A pointer to the Game object. This is the game instance for which the UI is being created.
 * @param gameFont The font to be used for drawing text in the UI.
 */
UserInterface::UserInterface(Game *gameInstance, const Font &gameFont) : font(gameFont), game(gameInstance) {
}

void UserInterface::DrawGameTextBoxAbove(const Font &font, const char *text, const Rectangle rect,
                                         // ReSharper disable once CppDFAConstantParameter
                                         const float fontSize,
                                         const Color fontColor) {
    DrawRectangleRounded(rect, 0.3f, 6, gameButtonlightPurple);

    const auto [xElementPosition, yElementPosition] = MeasureTextEx(font, text, fontSize, 2.0f);
    const float textX = rect.x + (rect.width - xElementPosition) / 2;
    const float textY = rect.y - yElementPosition - 4;

    DrawTextEx(font, text, {textX, textY}, fontSize, 2, fontColor);
}

void UserInterface::DrawGameTextBoxMiddle(const Font &font, const char *text, const Rectangle rect,
                                          // ReSharper disable once CppDFAConstantParameter
                                          const float fontSize, const Color fontColor) {
    DrawRectangleRounded(rect, 0.3f, 6, gameButtonlightPurple);

    const auto [xElementPosition, yElementPosition] = MeasureTextEx(font, text, fontSize, 2.0f);
    const float textX = rect.x + (rect.width - xElementPosition + 10) / 2;
    const float textY = rect.y + (rect.height - yElementPosition) / 2;

    DrawTextEx(font, text, {textX, textY}, fontSize, 2, fontColor);
}

void UserInterface::DrawMenuInterface() const {
    DrawTextEx(font, "TETRIS", {110, 40}, 100, 2, RAYWHITE);
    DrawMenuStartButton();
    DrawMenuHighScoresButtons();
    DrawMenuHighScoresButtons();
    DrawMenuSettingsButton();
    DrawMenuExitButton();
    DrawMenuUserButton();
}

void UserInterface::DrawGameInterface() const {
    DrawGameRestartButton();
    DrawGameOptionsButton();
    DrawGameScoreComponent();
    DrawGameBlocksComponent();
    DrawMenuUserButton();
}

void UserInterface::DrawHighScoresInterface() const {
}

void UserInterface::DrawGameRestartButton() const {
    auto restartButton = Button(Rectangle{315, 512, 180, 40}, "RESTART[R]");

    restartButton.UpdateButtonState(game->mousePosition);
    restartButton.DrawButton(font, RAYWHITE, 28.0f, gameButtonlightPurple, gameButtonHoverlightPurple);

    if (restartButton.isClicked) {
        game->Reset();
    }
}

void UserInterface::DrawGameOptionsButton() const {
    auto optionsButton = Button(Rectangle{315, 562, 180, 40}, "SETTINGS[ESC]");

    optionsButton.UpdateButtonState(game->mousePosition);
    optionsButton.DrawButton(font, RAYWHITE, 28.0f, gameButtonlightPurple, gameButtonHoverlightPurple);

    if (optionsButton.isClicked) {
        game->OptionsMenu();
    }
}

void UserInterface::DrawGameScoreComponent() const {
    DrawGameTextBoxAbove(font, "Score", {320, 55, 170, 60}, 38, WHITE);

    game->getScoreFontSize();

    char scoreText[10];
    snprintf(scoreText, sizeof(scoreText), "%d", game->getScore());
    const auto [xScorePosition, yScorePosition] = MeasureTextEx(font, scoreText, game->scoreFontSize, 2);

    DrawTextEx(font, scoreText, {320 + (170 - xScorePosition) / 2, 65}, game->scoreFontSize, 2, WHITE);
    if (game->maxScoreReached) {
        DrawTextEx(font, "MAX SCORE", {335, 110}, 30, 2, WHITE);
        DrawTextEx(font, "REACHED", {349, 130}, 30, 2, WHITE);
    }

    // Display "GAME OVER" when the gama ends
    if (game->IsGameOver()) {
        const std::string totalScoreMessage = std::string("TOTAL SCORE: ") + scoreText;

        /*  This helps to get the size of the "totalScoreMessage" and automatically get moved
            the most center position
        */
        const auto [x, y] = MeasureTextEx(font, totalScoreMessage.c_str(), game->gameOverFontSize, 0.5);
        DrawTextEx(font, "GAME OVER", {86, 220}, 34, 0.5, WHITE);
        DrawTextEx(font, totalScoreMessage.c_str(), {(320 - x) / 2, 245}, game->gameOverFontSize, 0.5, WHITE);
        DrawTextEx(font, "PREES ANY KEY", {47, 300}, 34, 0.5, WHITE);
        DrawTextEx(font, "TO PLAY AGAIN", {47, 325}, 34, 0.5, WHITE);
    }
}

void UserInterface::DrawGameBlocksComponent() const {
    DrawGameTextBoxAbove(font, "Next", {320, 215, 170, 180}, 38, WHITE);

    // Calling the method here, just before the next block container makes the next block
    // Appears on the container
    game->DrawGridAndBlocks();
}

void UserInterface::DrawMenuStartButton() const {
    // ReSharper disable once CppTooWideScopeInitStatement
    const Button startButton = CreateMenuCenteredButton(300, "START GAME");
    if (startButton.isClicked) game->currentMenuState = MenuState::GAME;
}


void UserInterface::DrawMenuHighScoresButtons() const {
    // ReSharper disable once CppTooWideScopeInitStatement
    const Button highScoresButton = CreateMenuCenteredButton(230, "HIGH SCORES");
    if (highScoresButton.isClicked) game->currentMenuState = MenuState::HIGH_SCORES;
}

void UserInterface::DrawMenuSettingsButton() const {
    // ReSharper disable once CppTooWideScopeInitStatement
    const Button settingsButton = CreateMenuCenteredButton(160, "SETTINGS");
    if (settingsButton.isClicked) game->currentMenuState = MenuState::MENU_SETTINGS;
}

void UserInterface::DrawMenuExitButton() const {
    // ReSharper disable once CppTooWideScopeInitStatement
    const Button exitButton = CreateMenuCenteredButton(90, "EXIT");
    if (exitButton.isClicked) {
        if (DrawExitConfirmation()) {
            game->currentMenuState = MenuState::EXIT;
        }
    }
}

bool UserInterface::DrawExitConfirmation() const {
    return true ;
}

void UserInterface::DrawMenuUserButton() const {
    // ReSharper disable once CppTooWideScopeInitStatement
    auto userButton = Button(Rectangle{460, 10, 30, 30}, "US");
    userButton.UpdateButtonState(game->mousePosition);
    userButton.DrawButton(font, RAYWHITE, 20, gameButtonlightPurple, gameButtonHoverlightPurple);
}

Vector2 UserInterface::GetCenteredPositionComparedWindow(const float yPosition) {
    const auto windowWidth = static_cast<float>(GetScreenWidth());
    const auto windowHeight = static_cast<float>(GetScreenHeight());

    Vector2 buttonPosition = {(windowHeight - (windowWidth / 2)) / 2, windowHeight - yPosition};
    buttonPosition.x = (windowWidth - (windowWidth / 2)) / 2;
    buttonPosition.y = (windowHeight - yPosition);

    return buttonPosition;
}

Button UserInterface::CreateMenuCenteredButton(const float yPosition,
                                               const std::string &text) const {
    const Vector2 buttonPosition = GetCenteredPositionComparedWindow(yPosition);
    auto button = Button(Rectangle{buttonPosition.x, buttonPosition.y, 250, 60}, text);

    button.UpdateButtonState(game->mousePosition);
    button.DrawButton(font, RAYWHITE, 40.0f, gameButtonlightPurple, gameButtonHoverlightPurple);

    return button;
}
