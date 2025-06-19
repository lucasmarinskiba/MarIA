#pragma once
#include <SFML/Graphics.hpp>

class GameOverScreen {
public:
    GameOverScreen(const sf::Font& font);

    void draw(sf::RenderWindow& window, int score = 0);

private:
    sf::Text title;
    sf::Text retry;
};
