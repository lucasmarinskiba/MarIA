#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class ResourceManager {
public:
    static std::map<std::string, sf::Texture> textures;  // Declaración
    static sf::Texture& getTexture(const std::string& filename);
    sf::Texture& loadTexture(const std::string& path);
    sf::Font& loadFont(const std::string& path);
    sf::SoundBuffer& loadSound(const std::string& path);
    void unloadAll();
private:
    std::map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<std::string, sf::SoundBuffer> sounds;
};

std::map<std::string, sf::Texture> ResourceManager::textures;

sf::Texture& ResourceManager::getTexture(const std::string& filename) {
    auto it = textures.find(filename);
    if (it == textures.end()) {
        sf::Texture texture;
        if (!texture.loadFromFile(filename)) {
            throw std::runtime_error("Failed to load texture: " + filename);
        }
        textures[filename] = texture;
        return textures[filename];
    }
    return it->second;
}
