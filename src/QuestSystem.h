#pragma once
#include <vector>
#include <string>
#include <functional>

struct Quest {
    std::string title;
    std::string description;
    bool completed = false;
    std::function<bool()> checkCompletion;
};

class QuestSystem {
public:
    void addQuest(const std::string& title, const std::string& description, std::function<bool()> checker);
    void update();
    const std::vector<Quest>& getActiveQuests() const { return activeQuests; }
private:
    std::vector<Quest> activeQuests;
};
