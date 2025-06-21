#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "ResourceManager.h"
#include "AnimatedSprite.h"

class NPC {
public:
    NPC(ResourceManager& rm, const sf::Vector2f& pos, const std::vector<std::string>& dialogues);

    void update(float dt, const sf::Vector2f& playerPos);
    void draw(sf::RenderWindow& window);
    void setTexture(const sf::Texture& texture);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const;

    bool canInteract(const sf::Vector2f& playerPos) const;
    std::string interact();

private:
    sf::Sprite sprite;
    std::vector<std::string> dialogues;
    size_t currentDialogue = 0;
    float interactRadius = 64.f;
};

class NPC : public AnimatedSprite {
public:
    NPC();
    void init(const sf::Texture& tex, const sf::Vector2f& pos, const std::vector<std::string>& dialogues);
    void save(std::ofstream& out) const;
    void load(std::ifstream& in, const sf::Texture& tex);

private:
    std::vector<std::string> dialogues;
    size_t currentDialogue = 0;
};
