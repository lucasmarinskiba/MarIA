#pragma once
#include <SFML/Graphics.hpp>

inline void drawBar(sf::RenderWindow& window, float x, float y, float width, float height, float percent, sf::Color fill, sf::Color bg) {
    sf::RectangleShape bgRect({width, height});
    bgRect.setPosition(x, y);
    bgRect.setFillColor(bg);
    window.draw(bgRect);

    sf::RectangleShape fillRect({width * percent, height});
    fillRect.setPosition(x, y);
    fillRect.setFillColor(fill);
    window.draw(fillRect);
}

inline void drawHUD(sf::RenderWindow& window, sf::Font& font, float health, float maxHealth, float faith, float maxFaith) {
    drawBar(window, 20, 20, 200, 24, health / maxHealth, sf::Color::Red, sf::Color(50,50,50));
    sf::Text tSalud("Salud", font, 18);
    tSalud.setPosition(24, 22); tSalud.setFillColor(sf::Color::White);
    window.draw(tSalud);

    drawBar(window, 20, 50, 200, 14, faith / maxFaith, sf::Color(100,180,255), sf::Color(50,50,50));
    sf::Text tFe("Fe", font, 12);
    tFe.setPosition(24, 52); tFe.setFillColor(sf::Color::White);
    window.draw(tFe);
}
