#pragma once

#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h" 
#include "ResourceManager.h"
class AnimatedSprite;

class NPC;  // Declaración adelantada en lugar de #include "NPC.h"

class Player : public AnimatedSprite {
public:
    Player(ResourceManager& rm);
    
    // Métodos de serialización
    void save(std::ofstream& out) const;
    void load(std::ifstream& in);
    
    void update(float dt);
    
    // Getters y setters
    float getHealth() const { return health; }
    float getMaxHealth() const { return maxHealth; }
    float getFaith() const { return faith; }
    float getMaxFaith() const { return maxFaith; }
    void setHealth(float h) { health = h; }
    void setFaith(float f) { faith = f; }
    void reset();

private:
    float health;
    float maxHealth;
    float faith;
    float maxFaith;
    float speed;
};

class Player {
public:
    Player(ResourceManager& rm);

    void update(float dt);
    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
    sf::Sprite& getSprite() { return sprite; }
    float getHealth() const { return health; }
    float getMaxHealth() const { return maxHealth; }
    float getFaith() const { return faith; }
    float getMaxFaith() const { return maxFaith; }

    void setHealth(float h) { health = h; }

private:
    AnimatedSprite* animatedSprite;
    float health = 100.f, maxHealth = 100.f;
    float faith = 100.f, maxFaith = 100.f;
    float speed = 200.f;
};

class Player : public AnimatedSprite {
public:
    Player(ResourceManager& rm);
    void save(std::ofstream& out) const;
    void load(std::ifstream& in);
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
