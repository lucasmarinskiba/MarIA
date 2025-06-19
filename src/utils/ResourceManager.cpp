#include "ResourceManager.h"

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
