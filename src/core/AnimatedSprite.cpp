#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite() : frameWidth(0), frameHeight(0), frameCount(1), frameTime(0.1f) {}

void AnimatedSprite::setTexture(const sf::Texture& texture, int fw, int fh, int fc, float ft) {
    sprite.setTexture(texture);
    frameWidth = fw; frameHeight = fh; frameCount = fc; frameTime = ft;
    sprite.setTextureRect(sf::IntRect(0,0,frameWidth,frameHeight));
}

void AnimatedSprite::setPosition(const sf::Vector2f& p) {
    sprite.setPosition(p);
}

void AnimatedSprite::update(float dt) {
    timeSinceLast += dt;
    if (timeSinceLast > frameTime) {
        currentFrame = (currentFrame + 1) % frameCount;
        sprite.setTextureRect(sf::IntRect(frameWidth * currentFrame, 0, frameWidth, frameHeight));
        timeSinceLast = 0.f;
    }
}


