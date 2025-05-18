#include "Quest.h"
#include "raylib.h"

DefeatMonsterQuest::DefeatMonsterQuest(int g) : goal(g), progress(0) {}

void DefeatMonsterQuest::onMonsterDefeated() {
    if (completed) return;
    progress++;
    checkProgress();
}

void DefeatMonsterQuest::onGoldEarned(int) {}

void DefeatMonsterQuest::checkProgress() {
    if (progress >= goal) completed = true;
}

void DefeatMonsterQuest::showStatus(int y) const {
    DrawText(TextFormat("Quest: Defeat Monsters %d/%d%s", progress, goal, completed ? " (Done)" : ""), 10, y, 20, completed ? GREEN : DARKGRAY);
}

EarnGoldQuest::EarnGoldQuest(int g) : goal(g), progress(0) {}

void EarnGoldQuest::onMonsterDefeated() {}

void EarnGoldQuest::onGoldEarned(int amount) {
    if (completed) return;
    progress += amount;
    checkProgress();
}

void EarnGoldQuest::checkProgress() {
    if (progress >= goal) completed = true;
}

void EarnGoldQuest::showStatus(int y) const {
    DrawText(TextFormat("Quest: Earn Gold %d/%d%s", progress, goal, completed ? " (Done)" : ""), 10, y, 20, completed ? GREEN : DARKGRAY);
}