#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#include <fstream>
#include <string>
#include <algorithm>

// Constructor principal
Player::Player(ResourceManager& rm)
    : AnimatedSprite(rm.getTexture("player.png")),
      health(100.f), maxHealth(100.f),
      faith(100.f), maxFaith(100.f),
      speed(200.f), experience(0), level(1), alive(true)
{
    const sf::Texture& tex = rm.loadTexture("assets/textures/player_sheet.png");
    setTexture(tex, 64, 64, 4, 0.14f);
    setPosition({100, 400});
}

// Actualización del jugador
void Player::update(float dt) {
    sf::Vector2f movement(0,0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += speed * dt;
    setPosition(getPosition() + movement);

    // Animar solo si se mueve
    if (movement.x != 0 || movement.y != 0)
        AnimatedSprite::update(dt);

    // Chequear si está vivo
    alive = (health > 0);
}

// Serialización
void Player::save(std::ofstream& out) const {
    out << getPosition().x << " " << getPosition().y << "\n";
    out << health << " " << faith << "\n";
    out << experience << " " << level << "\n";
    out << inventory.size() << "\n";
    for (const auto& item : inventory)
        out << item.name << " " << item.quantity << "\n";
}

void Player::load(std::ifstream& in) {
    float x, y;
    in >> x >> y;
    setPosition({x, y});
    in >> health >> faith;
    in >> experience >> level;
    size_t invCount;
    in >> invCount;
    inventory.clear();
    for (size_t i = 0; i < invCount; ++i) {
        Item it;
        in >> it.name >> it.quantity;
        inventory.push_back(it);
    }
    alive = (health > 0);
}

// Setters
void Player::setHealth(float h) {
    health = std::max(0.f, std::min(h, maxHealth));
    alive = (health > 0);
}
void Player::setFaith(float f) {
    faith = std::max(0.f, std::min(f, maxFaith));
}
void Player::addExperience(int amount) {
    experience += amount;
    // Ejemplo simple de subida de nivel
    if (experience >= 100) {
        level++;
        experience -= 100;
        // Podrías mejorar atributos aquí
    }
}
void Player::reset() {
    setPosition({100, 400});
    health = maxHealth;
    faith = maxFaith;
    alive = true;
    experience = 0;
    level = 1;
    inventory.clear();
}

// Inventario
void Player::addItem(const std::string& name, int quantity) {
    for (auto& item : inventory) {
        if (item.name == name) {
            item.quantity += quantity;
            return;
        }
    }
    inventory.push_back({name, quantity});
}
bool Player::hasItem(const std::string& name, int quantity) const {
    for (const auto& item : inventory) {
        if (item.name == name && item.quantity >= quantity)
            return true;
    }
    return false;
}
void Player::removeItem(const std::string& name, int quantity) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->name == name) {
            if (it->quantity > quantity) {
                it->quantity -= quantity;
            } else {
                inventory.erase(it);
            }
            return;
        }
    }
}

// Combate
void Player::attack(NPC& npc) {
    // Aquí iría la lógica de ataque contra NPC (debes definirla allí también)
}

void Player::takeDamage(float amount) {
    setHealth(health - amount);
}

// Interacción
void Player::interact(NPC& npc) {
    // Aquí podrías llamar a métodos de NPC para diálogos, etc.
}

// Si necesitas exponer el sprite (para el main)
sf::Sprite& Player::getSprite() {
    // Si AnimatedSprite tiene un método para esto, úsalo directamente
    // Aquí debes tener en AnimatedSprite: sf::Sprite sprite; protected/public
    return AnimatedSprite::getSprite();
}
