#pragma once
#include <string>
#include <vector>
#include "core/Player.h"
#include "core/Enemy.h"
#include "core/NPC.h"
#include "core/QuestSystem.h"

class SaveSystem {
public:
    static void save(const Player& player, const std::vector<Enemy>& enemies, const std::vector<NPC>& npcs, const QuestSystem& quests, const std::string& file = "save.txt");
    static bool load(Player& player, std::vector<Enemy>& enemies, const sf::Texture& enemyTex, std::vector<NPC>& npcs, const sf::Texture& npcTex, QuestSystem& quests, const std::string& file = "save.txt");
};
