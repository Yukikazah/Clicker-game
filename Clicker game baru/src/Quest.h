#pragma once
#include <memory>
#include <vector>

class Quest {
protected:
    bool completed = false;
public:
    virtual void checkProgress() = 0;
    virtual bool isCompleted() const { return completed; }
    virtual void showStatus(int y) const = 0;
    virtual void onMonsterDefeated() = 0;
    virtual void onGoldEarned(int amount) = 0;
    virtual ~Quest() = default;
};

class DefeatMonsterQuest : public Quest {
    int goal, progress;
public:
    DefeatMonsterQuest(int g);
    void onMonsterDefeated() override;
    void onGoldEarned(int) override;
    void checkProgress() override;
    void showStatus(int y) const override;
};

class EarnGoldQuest : public Quest {
    int goal, progress;
public:
    EarnGoldQuest(int g);
    void onMonsterDefeated() override;
    void onGoldEarned(int amount) override;
    void checkProgress() override;
    void showStatus(int y) const override;
};