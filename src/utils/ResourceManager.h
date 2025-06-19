#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class ResourceManager {
public:
    sf::Texture& loadTexture(const std::string& path);
    sf::Font& loadFont(const std::string& path);
    sf::SoundBuffer& loadSound(const std::string& path);
    void unloadAll();
private:
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<std::string, sf::SoundBuffer> sounds;
};
