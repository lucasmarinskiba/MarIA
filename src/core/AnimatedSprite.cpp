#pragma once
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

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

class AnimatedSprite : public sf::Drawable {
public:
    AnimatedSprite();
    void setTexture(const sf::Texture& texture, int frameWidth, int frameHeight, int frameCount, float frameTime);
    void setPosition(const sf::Vector2f& p);
    void update(float dt);

    sf::Vector2f getPosition() const;
protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::Sprite sprite;
    int frameWidth = 0, frameHeight = 0, frameCount = 1;
    int currentFrame = 0;
    float frameTime = 0.1f, timeSinceLast = 0.f;
};
