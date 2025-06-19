#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(const sf::Font& font) {
    title.setFont(font);
    title.setString("GAME OVER");
    title.setCharacterSize(64);
    title.setFillColor(sf::Color::Red);
    title.setPosition(420, 200);

    retry.setFont(font);
    retry.setString("Presiona ENTER para reintentar\nPresiona ESC para salir");
    retry.setCharacterSize(32);
    retry.setFillColor(sf::Color::White);
    retry.setPosition(370, 330);
}

void GameOverScreen::draw(sf::RenderWindow& window, int score) {
    window.draw(title);
    retry.setString("Presiona ENTER para reintentar\nPresiona ESC para salir\nScore: " + std::to_string(score));
    window.draw(retry);
}
