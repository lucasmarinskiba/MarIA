#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "utils/ResourceManager.h"

class NPC {
public:
    NPC(ResourceManager& rm, const sf::Vector2f& pos, const std::vector<std::string>& dialogues);

    void update(float dt, const sf::Vector2f& playerPos);
    void draw(sf::RenderWindow& window);

    bool canInteract(const sf::Vector2f& playerPos) const;
    std::string interact();

private:
    sf::Sprite sprite;
    std::vector<std::string> dialogues;
    size_t currentDialogue = 0;
    float interactRadius = 64.f;
};
