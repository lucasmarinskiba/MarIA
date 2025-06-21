#include "Level.h"
#include <fstream>  // Para std::ofstream
#include <string>   // Para std::string

Level::Level(ResourceManager& rm) {
    background.setTexture(rm.loadTexture("assets/textures/background.png"));
}

void Level::update(float, Player&, std::vector<NPC>&) {
    // Lógica de nivel si hace falta
}

void Level::draw(sf::RenderWindow& window, Player& player, std::vector<NPC>& npcs) {
    window.draw(background);
    for (auto& npc : npcs) npc.draw(window);
    player.draw(window);
}
