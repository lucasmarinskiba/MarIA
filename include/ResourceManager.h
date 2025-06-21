#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class ResourceManager {
public:
    static sf::Texture& getTexture(const std::string& filename);
    sf::Texture& loadTexture(const std::string& path);
    sf::Font& loadFont(const std::string& path);
    sf::SoundBuffer& loadSound(const std::string& path);
    void unloadAll();
private:
    static std::map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<std::string, sf::SoundBuffer> sounds;
};
