#include "SaveSystem.h"
#include <fstream>

void SaveSystem::save(const Player& player, const std::string& file) {
    std::ofstream out(file);
    if (!out) return;
    out << player.getPosition().x << ' ' << player.getPosition().y << '\n';
    out << player.getHealth() << ' ' << player.getFaith() << '\n';
    // Puedes guardar más datos aquí
}

bool SaveSystem::load(Player& player, const std::string& file) {
    std::ifstream in(file);
    if (!in) return false;
    float x, y, hp, faith;
    in >> x >> y >> hp >> faith;
    player.setPosition({x, y});
    player.setHealth(hp);
    player.setFaith(faith);
    // Puedes cargar más datos aquí
    return true;
}
