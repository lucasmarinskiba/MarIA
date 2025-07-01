#pragma once
#include <SFML/Graphics.hpp>

/**
 * @brief Clase AnimatedSprite para gestionar sprites animados usando SFML.
 */
class AnimatedSprite : public sf::Drawable {
public:
    /**
     * @brief Constructor por defecto.
     */
    AnimatedSprite() = default;

    /**
     * @brief Configura la textura y los parámetros de la animación.
     * @param texture Textura que contiene todos los frames.
     * @param frameWidth Ancho de cada frame.
     * @param frameHeight Alto de cada frame.
     * @param frameCount Número total de frames en la animación.
     * @param frameTime Tiempo (en segundos) que dura cada frame.
     */
    void setTexture(const sf::Texture& texture, int frameWidth, int frameHeight, int frameCount, float frameTime) {
        setAnimation(texture, frameWidth, frameHeight, frameCount, frameTime);
    }

    /**
     * @brief Configura la animación.
     * @param texture Textura que contiene todos los frames.
     * @param frameWidth Ancho de cada frame.
     * @param frameHeight Alto de cada frame.
     * @param frameCount Número total de frames en la animación.
     * @param frameTime Tiempo (en segundos) que dura cada frame.
     */
    void setAnimation(const sf::Texture& texture, 
                      int frameWidth, 
                      int frameHeight, 
                      int frameCount, 
                      float frameTime);
    
    /**
     * @brief Establece la posición del sprite.
     * @param position Nueva posición.
     */
    void setPosition(const sf::Vector2f& position);
    
    /**
     * @brief Actualiza la animación en función del tiempo transcurrido.
     * @param deltaTime Tiempo transcurrido desde la última actualización (en segundos).
     */
    void update(float deltaTime);
    
    /**
     * @brief Obtiene el área global del sprite.
     * @return Un sf::FloatRect con el área global.
     */
    sf::FloatRect getGlobalBounds() const;
    
    /**
     * @brief Obtiene la posición actual del sprite.
     * @return sf::Vector2f con la posición.
     */
    sf::Vector2f getPosition() const;

protected:
    /**
     * @brief Dibuja el sprite en el target especificado.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite sprite;
    sf::IntRect frameRect;
    int frameWidth = 0;
    int frameHeight = 0;
    int frameCount = 1;
    int currentFrame = 0;
    float frameTime = 0.1f;
    float timeSinceLast = 0.f;
};
