#include "raylib.h"
#include "BaseCharacter.h"

#ifndef CHARACTER_H //defined already in main
#define CHARACTER_H

class Character : public BaseCharacter
{
public:
    // -- Vector2 getWorldPos() { return worldPos; }
    // void setScreenPos(int winWidth, int winHeight); // we can define the function inside the class but we can also define out of the class
    virtual void tick(float deltaTime) override;
    Character(int winWidth, int winHeight);
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec(){ return weaponCollisionRec; }
    float getHealth() const { return health; } // if we plase the const before the return type, we can't change the value of the health
    void takeDamage(float damage);
    // -- void undoMovement();
    // -- Rectangle getCollisionRec();
private:    
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    float health{100.f};
};

#endif