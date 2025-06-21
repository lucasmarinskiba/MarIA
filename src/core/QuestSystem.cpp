#include "QuestSystem.h"
#include <fstream>  // Para std::ofstream
#include <string>   // Para std::string

void Quest::save(std::ofstream& out) const {
    out << title << '\n' << description << '\n' << completed << '\n';
}
void Quest::load(std::ifstream& in) {
    std::getline(in, title);
    std::getline(in, description);
    int comp = 0; in >> comp; completed = comp; in.ignore();
}

void QuestSystem::addQuest(const std::string& title, const std::string& description, std::function<bool()> checker) {
    activeQuests.push_back({title, description, false, checker});
}
void QuestSystem::update() {
    for (auto& quest : activeQuests) {
        if (!quest.completed && quest.checkCompletion())
            quest.completed = true;
    }
}
