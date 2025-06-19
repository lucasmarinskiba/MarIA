#include "SaveSystem.h"
#include <fstream>

void SaveSystem::save(const Player& player, const std::vector<Enemy>& enemies, const std::vector<NPC>& npcs, const QuestSystem& quests, const std::string& file) {
    std::ofstream out(file);
    if (!out) return;
    player.save(out);

    // Enemigos
    out << enemies.size() << '\n';
    for (const auto& e : enemies) e.save(out);

    // NPCs
    out << npcs.size() << '\n';
    for (const auto& n : npcs) n.save(out);

    // Misiones (igual que ejemplo anterior)
    const auto& qs = quests.getActiveQuests();
    out << qs.size() << '\n';
    for (const auto& quest : qs)
        quest.save(out);
}

bool SaveSystem::load(Player& player, std::vector<Enemy>& enemies, const sf::Texture& enemyTex, std::vector<NPC>& npcs, const sf::Texture& npcTex, QuestSystem& quests, const std::string& file) {
    std::ifstream in(file);
    if (!in) return false;
    player.load(in);

    size_t nEnemies;
    in >> nEnemies;
    enemies.resize(nEnemies);
    for (size_t i = 0; i < nEnemies; ++i) {
        enemies[i].load(in, enemyTex);
    }

    size_t nNpcs;
    in >> nNpcs;
    npcs.resize(nNpcs);
    for (size_t i = 0; i < nNpcs; ++i) {
        // Si tienes diálogos default, pásalos a init después de load
        npcs[i].load(in, npcTex);
    }

    int nQuests;
    in >> nQuests; in.ignore();
    auto& qs = quests.getActiveQuests();
    for (int i = 0; i < nQuests && i < (int)qs.size(); ++i) {
        qs[i].load(in);
    }
    return true;
}
