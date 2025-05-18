#include "Monster.h"
#include "raylib.h"

Monster::Monster(int health) : maxHp(health), hp(health), rect({ 200, 200, 200, 200 }) {}

bool Monster::isClicked(Vector2 mouse) {
    return CheckCollisionPointRec(mouse, rect);
}

bool Monster::takeDamage(int dmg) {
    hp -= dmg;
    return hp <= 0;
}

void Monster::draw() const {
    DrawRectangleRec(rect, RED);
    DrawText("Monster", rect.x + 50, rect.y + 80, 20, WHITE);
    DrawText(TextFormat("HP: %d", hp), rect.x + 50, rect.y + 110, 20, WHITE);
}

void Monster::reset() {
    hp = maxHp;
}