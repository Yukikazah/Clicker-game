#include "raylib.h"
#include "Monster.h"
#include "Player.h"
#include "QuestManager.h"
#include "Quest.h"

int main() {
    InitWindow(600, 400, "Clicker Game");
    SetTargetFPS(60);

    Player player;
    Monster monster(10);
    QuestManager questManager;
    questManager.addQuest(std::make_shared<DefeatMonsterQuest>(5));
    questManager.addQuest(std::make_shared<EarnGoldQuest>(25));

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