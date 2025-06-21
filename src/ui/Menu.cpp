#include "Menu.h"
#include <fstream>  // Para std::ofstream
#include <string>   // Para std::string

Menu::Menu(const sf::Font& font) {
    title.setFont(font);
    title.setString("MARIA GAME");
    title.setCharacterSize(64);
    title.setFillColor(sf::Color::White);
    title.setPosition(340, 100);

    options.resize(2);
    options[0].setFont(font);
    options[0].setString("Presiona ENTER para jugar");
    options[0].setCharacterSize(32);
    options[0].setFillColor(sf::Color(200,200,200));
    options[0].setPosition(370, 220);

    options[1].setFont(font);
    options[1].setString("Presiona ESC para salir");
    options[1].setCharacterSize(28);
    options[1].setFillColor(sf::Color(150,150,150));
    options[1].setPosition(420, 280);
}

void Menu::drawMainMenu(sf::RenderWindow& window) {
    window.draw(title);
    for (auto& opt : options) window.draw(opt);
}

void Menu::drawPauseMenu(sf::RenderWindow& window) {
    sf::RectangleShape rect(sf::Vector2f(400, 180));
    rect.setPosition(440, 260);
    rect.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(rect);

    sf::Text paused("PAUSA", title.getFont(), 52);
    paused.setPosition(570, 275);
    paused.setFillColor(sf::Color::White);
    window.draw(paused);

    sf::Text resume("Presiona ESC para reanudar", title.getFont(), 26);
    resume.setPosition(495, 340);
    resume.setFillColor(sf::Color(200, 200, 200));
    window.draw(resume);

    sf::Text quit("Presiona Q para salir", title.getFont(), 22);
    quit.setPosition(545, 380);
    quit.setFillColor(sf::Color(150,150,150));
    window.draw(quit);
}
