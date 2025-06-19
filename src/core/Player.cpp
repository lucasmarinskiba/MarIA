#include "Player.h"

Player::Player(ResourceManager& rm) {
    sprite.setTexture(rm.loadTexture("assets/textures/player.png"));
    sprite.setPosition(100, 400);
}

void Player::update(float dt) {
    sf::Vector2f movement(0,0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += speed * dt;
    sprite.move(movement);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}
