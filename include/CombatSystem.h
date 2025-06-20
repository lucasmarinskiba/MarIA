#pragma once
#include <vector>
#include "core/Player.h"
#include "core/NPC.h"

class Enemy {
public:
    Enemy(sf::Texture& tex, sf::Vector2f pos);

    void update(float dt, const sf::Vector2f& playerPos);
    void draw(sf::RenderWindow& window);
    void takeDamage(float dmg);

    sf::Vector2f getPosition() const;
    bool isAlive() const { return alive; }
private:
    sf::Sprite sprite;
    float health = 30.f;
    bool alive = true;
};

class CombatSystem {
public:
    void addEnemy(const Enemy& enemy);
    void update(float dt, const sf::Vector2f& playerPos);
    void playerAttack(const sf::Vector2f& attackPos, float radius, float damage);
    void draw(sf::RenderWindow& window);
    std::vector<Enemy>& getEnemies() { return enemies; }
private:
    std::vector<Enemy> enemies;
};
