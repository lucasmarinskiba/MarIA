#pragma once
#include "core/AnimatedSprite.h"
#include <SFML/Graphics.hpp>

class Enemy : public AnimatedSprite {
public:
    Enemy();
    void init(const sf::Texture& tex, const sf::Vector2f& pos);
    void save(std::ofstream& out) const;
    void load(std::ifstream& in, const sf::Texture& tex);

    void setAlive(bool a) { alive = a; }
    bool isAlive() const { return alive; }
    void setHealth(float h) { health = h; }
    float getHealth() const { return health; }

private:
    bool alive = true;
    float health = 30.f;
};
