#pragma once
#include <string>
#include "core/Player.h"
#include "core/QuestSystem.h"

class SaveSystem {
public:
    static void save(const Player& player, const QuestSystem& quests, const std::string& file = "save.txt");
    static bool load(Player& player, QuestSystem& quests, const std::string& file = "save.txt");
};
