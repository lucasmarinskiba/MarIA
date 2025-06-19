#pragma once
#include <SFML/Graphics.hpp>
#include <string>

inline void DrawBar(sf::RenderWindow& window, float x, float y, float width, float height, float percent, sf::Color colorFill, sf::Color colorBg) {
    sf::RectangleShape bg(sf::Vector2f(width, height));
    bg.setPosition(x, y);
    bg.setFillColor(colorBg);
    window.draw(bg);

    sf::RectangleShape fill(sf::Vector2f(width * percent, height));
    fill.setPosition(x, y);
    fill.setFillColor(colorFill);
    window.draw(fill);
}

inline void DrawHUD(sf::RenderWindow& window, sf::Font& font, float health, float maxHealth, float faith, float maxFaith) {
    DrawBar(window, 20, 20, 200, 24, health / maxHealth, sf::Color::Red, sf::Color(50,50,50));
    sf::Text salud("Salud", font, 18);
    salud.setPosition(24, 22);
    salud.setFillColor(sf::Color::White);
    window.draw(salud);

    DrawBar(window, 20, 50, 200, 14, faith / maxFaith, sf::Color(100,180,255), sf::Color(50,50,50));
    sf::Text fe("Fe", font, 12);
    fe.setPosition(24, 52);
    fe.setFillColor(sf::Color::White);
    window.draw(fe);
}
