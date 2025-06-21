#include "CombatSystem.h"
#include <fstream>  // Para std::ofstream
#include <string>   // Para std::string
#include <cmath>

Enemy::Enemy(sf::Texture& tex, sf::Vector2f pos) {
    sprite.setTexture(tex);
    sprite.setPosition(pos);
}
void Enemy::update(float dt, const sf::Vector2f& playerPos) {
    if (!alive) return;
    sf::Vector2f dir = playerPos - sprite.getPosition();
    float len = std::sqrt(dir.x*dir.x + dir.y*dir.y);
    if (len > 2.f) {
        dir /= len;
        sprite.move(dir * 50.f * dt); // Velocidad enemiga
    }
}
void Enemy::draw(sf::RenderWindow& window) {
    if (alive) window.draw(sprite);
}
void Enemy::takeDamage(float dmg) {
    health -= dmg;
    if (health <= 0) alive = false;
}
sf::Vector2f Enemy::getPosition() const { return sprite.getPosition(); }

void CombatSystem::addEnemy(const Enemy& enemy) { enemies.push_back(enemy); }
void CombatSystem::update(float dt, const sf::Vector2f& playerPos) {
    for (auto& e : enemies) e.update(dt, playerPos);
}
void CombatSystem::playerAttack(const sf::Vector2f& attackPos, float radius, float damage) {
    for (auto& e : enemies) {
        if (e.isAlive()) {
            sf::Vector2f delta = e.getPosition() - attackPos;
            float dist = std::sqrt(delta.x*delta.x + delta.y*delta.y);
            if (dist < radius) e.takeDamage(damage);
        }
    }
}
void CombatSystem::draw(sf::RenderWindow& window) {
    for (auto& e : enemies) e.draw(window);
}
