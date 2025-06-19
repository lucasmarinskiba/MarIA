#pragma once
#include <SFML/Graphics.hpp>
#include "utils/ResourceManager.h"

class Player {
public:
    Player(ResourceManager& rm);

    void update(float dt);
    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
    float getHealth() const { return health; }
    float getMaxHealth() const { return maxHealth; }
    float getFaith() const { return faith; }
    float getMaxFaith() const { return maxFaith; }

private:
    sf::Sprite sprite;
    float health = 100.f, maxHealth = 100.f;
    float faith = 100.f, maxFaith = 100.f;
    float speed = 200.f;
};
