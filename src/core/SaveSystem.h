#pragma once
#include <string>
#include "core/Player.h"

class SaveSystem {
public:
    static void save(const Player& player, const std::string& file = "save.txt");
    static bool load(Player& player, const std::string& file = "save.txt");
};
