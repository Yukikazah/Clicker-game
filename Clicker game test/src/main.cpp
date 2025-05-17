#include "raylib.h"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// Quest system (Observer)
class QuestObserver {
public:
    virtual void onMonsterDefeated() = 0;
    virtual void onGoldEarned(int amount) = 0;
    virtual ~QuestObserver() = default;
};

class Quest {
protected:
    bool completed = false;
public:
    virtual void checkProgress() = 0;
    virtual bool isCompleted() const { return completed; }
    virtual void showStatus(int y) const = 0;
    virtual void onMonsterDefeated() = 0;
    virtual void onGoldEarned(int amount) = 0;
};

class DefeatMonsterQuest : public Quest {
    int goal, progress;
public:
    DefeatMonsterQuest(int g) : goal(g), progress(0) {}

    void onMonsterDefeated() override {
        if (completed) return;
        progress++;
        checkProgress();
    }

    void onGoldEarned(int) override {}

    void checkProgress() override {
        if (progress >= goal) {
            completed = true;
        }
    }

    void showStatus(int y) const override {
        DrawText(TextFormat("Quest: Defeat Monsters %d/%d%s", progress, goal, completed ? " (Done)" : ""), 10, y, 20, completed ? GREEN : DARKGRAY);
    }
};

class EarnGoldQuest : public Quest {
    int goal, progress;
public:
    EarnGoldQuest(int g) : goal(g), progress(0) {}

    void onMonsterDefeated() override {}

    void onGoldEarned(int amount) override {
        if (completed) return;
        progress += amount;
        checkProgress();
    }

    void checkProgress() override {
        if (progress >= goal) {
            completed = true;
        }
    }

    void showStatus(int y) const override {
        DrawText(TextFormat("Quest: Earn Gold %d/%d%s", progress, goal, completed ? " (Done)" : ""), 10, y, 20, completed ? GREEN : DARKGRAY);
    }
};

class QuestManager {
    vector<shared_ptr<Quest>> quests;
public:
    void addQuest(shared_ptr<Quest> quest) {
        quests.push_back(quest);
    }

    void notifyMonsterDefeated() {
        for (auto& q : quests)
            q->onMonsterDefeated();
    }

    void notifyGoldEarned(int gold) {
        for (auto& q : quests)
            q->onGoldEarned(gold);
    }

    void showQuests() const {
        int y = 60;
        for (auto& q : quests) {
            q->showStatus(y);
            y += 25;
        }
    }
};

class Monster {
public:
    int maxHp;
    int hp;
    Rectangle rect;

    Monster(int health) : maxHp(health), hp(health), rect({ 200, 200, 200, 200 }) {}

    bool isClicked(Vector2 mouse) {
        return CheckCollisionPointRec(mouse, rect);
    }

    bool takeDamage(int dmg) {
        hp -= dmg;
        return hp <= 0;
    }

    void draw() const {
        DrawRectangleRec(rect, RED);
        DrawText("Monster", rect.x + 50, rect.y + 80, 20, WHITE);
        DrawText(TextFormat("HP: %d", hp), rect.x + 50, rect.y + 110, 20, WHITE);
    }

    void reset() {
        hp = maxHp;
    }
};

class Player {
public:
    int gold = 0;
    int damage = 1;

    void earnGold(int g) {
        gold += g;
    }
};

int main() {
    InitWindow(600, 400, "Clicker Game");
    SetTargetFPS(60);

    Player player;
    Monster monster(10);
    QuestManager questManager;
    questManager.addQuest(make_shared<DefeatMonsterQuest>(5));
    questManager.addQuest(make_shared<EarnGoldQuest>(25));

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(TextFormat("Gold: %d", player.gold), 10, 10, 20, DARKBLUE);
        monster.draw();
        questManager.showQuests();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetMousePosition();
            if (monster.isClicked(mouse)) {
                if (monster.takeDamage(player.damage)) {
                    player.earnGold(5);
                    questManager.notifyMonsterDefeated();
                    questManager.notifyGoldEarned(5);
                    monster.reset();
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
