#pragma once
#include <SFML/Graphics.hpp>
#include "core/QuestSystem.h"

class QuestSelector {
public:
    QuestSelector(const sf::Font& font, const QuestSystem& questSystem);

    void draw(sf::RenderWindow& window);
    void next();
    void prev();
    int getSelected() const;

private:
    const QuestSystem& questSystem;
    int selected = 0;
    sf::Font font;
};
