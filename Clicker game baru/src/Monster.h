#pragma once
#include "raylib.h"

class Monster {
public:
    int maxHp;
    int hp;
    Rectangle rect;

    Monster(int health);
    bool isClicked(Vector2 mouse);
    bool takeDamage(int dmg);
    void draw() const;
    void reset();
};