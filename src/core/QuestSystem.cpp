#include "QuestSystem.h"

void QuestSystem::addQuest(const std::string& title, const std::string& description, std::function<bool()> checker) {
    activeQuests.push_back({title, description, false, checker});
}
void QuestSystem::update() {
    for (auto& quest : activeQuests) {
        if (!quest.completed && quest.checkCompletion()) {
            quest.completed = true;
            // Podrías mostrar un mensaje o reproducir un sonido aquí
        }
    }
}
