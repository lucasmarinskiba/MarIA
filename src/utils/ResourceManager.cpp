#include "ResourceManager.h"
#include <fstream>  // Para std::ofstream
#include <string>   // Para std::string

std::map<std::string, sf::Texture> ResourceManager::textures;

sf::Texture& ResourceManager::getTexture(const std::string& filename) {
    auto it = textures.find(filename);
    if (it == textures.end()) {
        sf::Texture texture;
        if (!texture.loadFromFile(filename)) {
            // Manejar error
        }
        textures[filename] = texture;
        return textures[filename];
    }
    return it->second;
}

sf::Texture& ResourceManager::loadTexture(const std::string& path) {
    auto& tex = textures[path];
    if (tex.getSize().x == 0) tex.loadFromFile(path);
    return tex;
}
sf::Font& ResourceManager::loadFont(const std::string& path) {
    auto& font = fonts[path];
    if (font.getInfo().family.empty()) font.loadFromFile(path);
    return font;
}
sf::SoundBuffer& ResourceManager::loadSound(const std::string& path) {
    auto& snd = sounds[path];
    if (snd.getSampleCount() == 0) snd.loadFromFile(path);
    return snd;
}
void ResourceManager::unloadAll() {
    textures.clear();
    fonts.clear();
    sounds.clear();
}
