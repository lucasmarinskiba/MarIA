#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#include <fstream>  // Para std::ofstream
#include <string>   // Para std::string

// En Player.cpp
Player::Player() 
    : health(100), faith(50)  // Inicialización directa
{
    // ...
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
    window.draw(sprite);
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
