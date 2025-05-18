#include "QuestManager.h"

void QuestManager::addQuest(std::shared_ptr<Quest> quest) {
    quests.push_back(quest);
}

void QuestManager::notifyMonsterDefeated() {
    for (auto& q : quests) q->onMonsterDefeated();
}

void QuestManager::notifyGoldEarned(int gold) {
    for (auto& q : quests) q->onGoldEarned(gold);
}

void QuestManager::showQuests() const {
    int y = 60;
    for (auto& q : quests) {
        q->showStatus(y);
        y += 25;
    }
}