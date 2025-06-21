#pragma once
#include <string>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "NPC.h"
#include "QuestSystem.h"

class SaveSystem {
public:
    static void save(const Player& player, const std::vector<Enemy>& enemies, const std::vector<NPC>& npcs, const QuestSystem& quests, const std::string& file = "save.txt");
    static bool load(Player& player, std::vector<Enemy>& enemies, const sf::Texture& enemyTex, std::vector<NPC>& npcs, const sf::Texture& npcTex, QuestSystem& quests, const std::string& file = "save.txt");
};
