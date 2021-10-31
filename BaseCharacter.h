#include "raylib.h"
#include "raymath.h"

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter{
    public:
        BaseCharacter();
        Vector2 getWorldPos() { return worldPos; }
        void undoMovement();
        Rectangle getCollisionRec();
        virtual void tick(float deltaTime);
        virtual Vector2 getScreenPos() = 0;
        // we dont need to define the function in parent class so we will pure virtual function, we only have to define it here.
        // when we define it in the parent class, it will be a pure virtual function, and we will have to define it in the child class only. It is called as abstract class.
        bool getAlive() { return alive; }
        void setAlive(bool alive) { this->alive = alive; }
    protected:
        Texture2D texture = LoadTexture("characters/knight_idle_spritesheet.png");
        Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");
        Texture2D run = LoadTexture("characters/knight_run_spritesheet.png");
        // Vector2 screenPos{};
        Vector2 worldPos{};
        Vector2 worldPosLastFrame{};
        // 1:right, -1: left
        float rightleft{1.f};
        // animation data
        float runningTime{};
        int frame{};
        const int maxFrame{6};
        const float updateTime{1.0f / 12.0f};
        float speed{4.f};
        float width{};
        float height{};
        bool alive{true};
        Vector2 velocity{}; // contains info. regarding the direction of movement and the distance it should move the frame.
};

#endif