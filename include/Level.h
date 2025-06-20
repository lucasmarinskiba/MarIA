#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "core/NPC.h"
#include "core/Player.h"
#include "utils/ResourceManager.h"

class Level {
public:
    Level(ResourceManager& rm);

    void update(float dt, Player& player, std::vector<NPC>& npcs);
    void draw(sf::RenderWindow& window, Player& player, std::vector<NPC>& npcs);

private:
    sf::Sprite background;
};
