#include "NPC.h"
#include <cmath>
#include <fstream>  // Para std::ofstream
#include <string>   // Para std::string

NPC::NPC() : currentDialogue(0), interactRadius(50.0f) {}

void NPC::setTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
}

void NPC::save(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        sf::Vector2f pos = sprite.getPosition();
        file << pos.x << " " << pos.y << " " << currentDialogue;
        file.close();
    }
}

NPC::NPC(ResourceManager& rm, const sf::Vector2f& pos, const std::vector<std::string>& dialogues)
    : dialogues(dialogues) {
    sprite.setTexture(rm.loadTexture("assets/textures/npc.png"));
    sprite.setPosition(pos);
}

void NPC::update(float, const sf::Vector2f&) {
    // Animaciones o lógica futura
}

void NPC::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool NPC::canInteract(const sf::Vector2f& playerPos) const {
    sf::Vector2f delta = playerPos - sprite.getPosition();
    return std::sqrt(delta.x * delta.x + delta.y * delta.y) < interactRadius;
}

std::string NPC::interact() {
    if (dialogues.empty()) return "";
    currentDialogue = (currentDialogue + 1) % dialogues.size();
    return dialogues[currentDialogue];
}

void NPC::init(const sf::Texture& tex, const sf::Vector2f& pos, const std::vector<std::string>& d) {
    setTexture(tex, 64, 64, 4, 0.22f);
    setPosition(pos);
    dialogues = d;
    currentDialogue = 0;
}

void NPC::save(std::ofstream& out) const {
    auto pos = getPosition();
    out << pos.x << ' ' << pos.y << ' ' << currentDialogue << ' ' << dialogues.size() << '\n';
    for (const auto& s : dialogues) out << s << '\n';
}

void NPC::load(std::ifstream& in, const sf::Texture& tex) {
    float x, y; size_t idx, count;
    in >> x >> y >> idx >> count;
    setTexture(tex, 64, 64, 4, 0.22f);
    setPosition({x, y});
    currentDialogue = idx;
    dialogues.clear();
    in.ignore();
    for (size_t i = 0; i < count; ++i) {
        std::string line;
        std::getline(in, line);
        dialogues.push_back(line);
    }
}
