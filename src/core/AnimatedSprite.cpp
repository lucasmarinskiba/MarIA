#include "AnimatedSprite.h"
#include <fstream>  // Para std::ofstream
#include <string>   // Para std::string

AnimatedSprite::AnimatedSprite() {}

void AnimatedSprite::setTexture(const sf::Texture& texture, int fw, int fh, int fc, float ft) {
    sprite.setTexture(texture);
    frameWidth = fw;
    frameHeight = fh;
    frameCount = fc;
    frameTime = ft;
    currentFrame = 0;
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
}

void AnimatedSprite::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

void AnimatedSprite::update(float dt) {
    timeSinceLast += dt;
    if (timeSinceLast > frameTime) {
        currentFrame = (currentFrame + 1) % frameCount;
        sprite.setTextureRect(sf::IntRect(frameWidth * currentFrame, 0, frameWidth, frameHeight));
        timeSinceLast = 0.f;
    }
}

sf::Vector2f AnimatedSprite::getPosition() const {
    return sprite.getPosition();
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

sf::Sprite& AnimatedSprite::getSprite() {
    return sprite; // Implementación del nuevo método
}

void AnimatedSprite::move(sf::Vector2f offset) {
    sprite.move(offset);
}

void AnimatedSprite::setAnimation(const sf::Texture& texture, int fw, int fh, int fc, float fd) {
    sprite.setTexture(texture);
    frameWidth = fw;
    frameHeight = fh;
    frameCount = fc;
    frameDuration = fd;
    
    // Configurar el primer frame
    frameRect = {0, 0, frameWidth, frameHeight};
    sprite.setTextureRect(frameRect);
}

