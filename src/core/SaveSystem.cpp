#include "SaveSystem.h"
#include <fstream>

void SaveSystem::save(const Player& player, const QuestSystem& quests, const std::string& file) {
    std::ofstream out(file);
    if (!out) return;
    out << player.getPosition().x << ' ' << player.getPosition().y << '\n';
    out << player.getHealth() << ' ' << player.getFaith() << '\n';

    // Guardar misiones
    const auto& qs = quests.getActiveQuests();
    out << qs.size() << '\n';
    for (const auto& quest : qs)
        quest.save(out);
}

bool SaveSystem::load(Player& player, QuestSystem& quests, const std::string& file) {
    std::ifstream in(file);
    if (!in) return false;
    float x, y, hp, faith;
    in >> x >> y >> hp >> faith;
    player.setPosition({x, y});
    player.setHealth(hp);
    player.setFaith(faith);
    int n = 0;
    in >> n; in.ignore();
    auto& qs = quests.getActiveQuests();
    for (int i = 0; i < n && i < (int)qs.size(); ++i) {
        qs[i].load(in);
    }
    return true;
}
