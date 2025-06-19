#include "NPC.h"
#include <cmath>

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
