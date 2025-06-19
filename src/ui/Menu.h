#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Menu {
public:
    Menu(const sf::Font& font);

    void drawMainMenu(sf::RenderWindow& window);
    void drawPauseMenu(sf::RenderWindow& window);

private:
    sf::Text title;
    std::vector<sf::Text> options;
};
