#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class OptionsMenu {
public:
    OptionsMenu(const sf::Font& font);

    void draw(sf::RenderWindow& window);
    void nextResolution();
    void prevResolution();
    sf::Vector2u getSelectedResolution() const;
    int getFPS() const;

private:
    std::vector<sf::Vector2u> resolutions;
    size_t selected = 0;
    int fps = 60;
    sf::Text title;
    sf::Text resText;
    sf::Text fpsText;
};
