#pragma once
#include <SFML/Graphics.hpp>
#include "core/QuestSystem.h"

inline void drawQuestHUD(sf::RenderWindow& window, const sf::Font& font, const QuestSystem& questSystem) {
    const auto& quests = questSystem.getActiveQuests();
    if (quests.empty()) return;

    sf::RectangleShape panel({320, 30.f + 40.f * quests.size()});
    panel.setPosition(900, 20);
    panel.setFillColor(sf::Color(0,0,0,170));
    window.draw(panel);

    sf::Text title("Misiones:", font, 22);
    title.setPosition(910, 25);
    title.setFillColor(sf::Color::Yellow);
    window.draw(title);

    float y = 55;
    for (const auto& quest : quests) {
        sf::Text questText(quest.title + (quest.completed ? " (Completado)" : ""), font, 18);
        questText.setPosition(910, y);
        questText.setFillColor(quest.completed ? sf::Color(100,200,100) : sf::Color::White);
        window.draw(questText);
        y += 34;
    }
}
