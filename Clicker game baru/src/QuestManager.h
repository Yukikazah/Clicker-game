#pragma once
#include "Quest.h"

class QuestManager {
    std::vector<std::shared_ptr<Quest>> quests;
public:
    void addQuest(std::shared_ptr<Quest> quest);
    void notifyMonsterDefeated();
    void notifyGoldEarned(int gold);
    void showQuests() const;
};