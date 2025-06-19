#include "OptionsMenu.h"

OptionsMenu::OptionsMenu(const sf::Font& font) {
    resolutions = { {1280,720}, {1600,900}, {1920,1080} };

    title.setFont(font);
    title.setString("OPCIONES");
    title.setCharacterSize(50);
    title.setPosition(480, 90);
    title.setFillColor(sf::Color::White);

    resText.setFont(font);
    resText.setCharacterSize(28);
    resText.setFillColor(sf::Color::Yellow);
    resText.setPosition(420, 200);

    fpsText.setFont(font);
    fpsText.setCharacterSize(28);
    fpsText.setFillColor(sf::Color::Green);
    fpsText.setPosition(420, 260);
}

void OptionsMenu::draw(sf::RenderWindow& window) {
    window.draw(title);
    resText.setString("Resolucion: " + std::to_string(resolutions[selected].x) + "x" + std::to_string(resolutions[selected].y));
    window.draw(resText);
    fpsText.setString("FPS: " + std::to_string(fps));
    window.draw(fpsText);
}

void OptionsMenu::nextResolution() { selected = (selected + 1) % resolutions.size(); }
void OptionsMenu::prevResolution() { selected = (selected + resolutions.size() - 1) % resolutions.size(); }
sf::Vector2u OptionsMenu::getSelectedResolution() const { return resolutions[selected]; }
int OptionsMenu::getFPS() const { return fps; }
