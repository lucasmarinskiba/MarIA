#include "Player.h"
#include "AnimatedSprite.h"
#include <SFML/Window/Keyboard.hpp>
#include <fstream>  // Para std::ofstream
#include <string>   // Para std::string

Player::Player() {
    animatedSprite = new AnimatedSprite(); // Inicializar el sprite animado
    health = 100;
    faith = 50;
    maxHealth = 100;
    maxFaith = 100;
}

void Player::update(sf::Time deltaTime) {
    animatedSprite->update(deltaTime); // Llamar correctamente al update
}

Player::Player(ResourceManager& rm) {
    const sf::Texture& tex = rm.loadTexture("assets/textures/player_sheet.png");
    setTexture(tex, 64, 64, 4, 0.14f); // 4 frames, 0.14s por frame
    setPosition({100, 400});
}

void Player::update(float dt) {
    sf::Vector2f movement(0,0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += speed * dt;
    setPosition(getPosition() + movement);

    // Solo animar cuando el jugador se mueve
    if (movement.x != 0 || movement.y != 0)
        AnimatedSprite::update(dt);
    
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(animatedSprite->getSprite());
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

void Player::save(std::ofstream& out) const {
    auto pos = getPosition();
    out << pos.x << ' ' << pos.y << ' ' << health << ' ' << faith << '\n';
}

void Player::load(std::ifstream& in) {
    float x, y;
    in >> x >> y >> health >> faith;
    setPosition({x, y});
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << player.getHealth() << " " << player.getFaith();
    return os;
}

std::istream& operator>>(std::istream& is, Player& player) {
    float health, faith;
    is >> health >> faith;
    player.setHealth(health);
    player.setFaith(faith);
    return is;
}
