#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter(){

}

void BaseCharacter::undoMovement(){
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec(){
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * 4.f,
        height * 4.f
    };
}

void BaseCharacter::tick(float deltaTime){
    
    
    worldPosLastFrame = worldPos;

    // update animation character-------------------------------------------------------------------
    // float dT{GetFrameTime()};

    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrame)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        // if x=1, y=1 then z=1.414; /results diagonal speed more, hence vector2normalize
        // set worldPos = worldPos + velocity
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        (velocity.x < 0.f) ? rightleft = -1.f : rightleft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

    velocity = {};

    // draw the character -----------------------------------------------------------------
    Rectangle source{frame * width, 0.f, rightleft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, 4.0f * width, 4.0f * height};
    Vector2 origin{};
    DrawTexturePro(texture, source, dest, origin, 0.f, WHITE);
}