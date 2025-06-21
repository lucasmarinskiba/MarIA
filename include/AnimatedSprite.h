#pragma once
#include <SFML/Graphics.hpp>

class Player;  // Declaración adelantada

class AnimatedSprite {
public:
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window);
    // ... otras funciones ...
};

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
