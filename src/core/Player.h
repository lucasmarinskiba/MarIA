#pragma once
#include <SFML/Graphics.hpp>
#include "utils/ResourceManager.h"
#include "core/AnimatedSprite.h"
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

class Player : public AnimatedSprite {
public:
    Player(ResourceManager& rm);

    void update(float dt);
    // ... tus getters/setters y stats ...

private:
    float health = 100.f, maxHealth = 100.f;
    float faith = 100.f, maxFaith = 100.f;
    float speed = 200.f;
};

// Más métodos...
void setPosition(const sf::Vector2f& pos) { sprite.setPosition(pos); }
void setHealth(float h) { health = h; }
void setFaith(float f) { faith = f; }
void reset() { setPosition({100, 400}); setHealth(maxHealth); setFaith(maxFaith); }
