#include "QuestSelector.h"
#include <fstream>  // Para std::ofstream
#include <string>   // Para std::string

QuestSelector::QuestSelector(const sf::Font& font, const QuestSystem& qs)
    : questSystem(qs), font(font) {}

void QuestSelector::draw(sf::RenderWindow& window) {
    const auto& quests = questSystem.getActiveQuests();
    if (quests.empty()) return;
    sf::RectangleShape bg({400, 220});
    bg.setFillColor(sf::Color(0,0,0,190));
    bg.setPosition(440, 200);
    window.draw(bg);

    sf::Text title("Selecciona una mision:", font, 30);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(460, 210);
    window.draw(title);

    float y = 260;
    for (size_t i = 0; i < quests.size(); ++i) {
        sf::Text text(quests[i].title, font, 22);
        text.setFillColor(i == selected ? sf::Color::Cyan : sf::Color::White);
        text.setPosition(470, y);
        window.draw(text);
        y += 40;
    }
}

void QuestSelector::next() {
    int n = questSystem.getActiveQuests().size();
    if (n > 0) selected = (selected + 1) % n;
}
void QuestSelector::prev() {
    int n = questSystem.getActiveQuests().size();
    if (n > 0) selected = (selected + n - 1) % n;
}
int QuestSelector::getSelected() const { return selected; }
