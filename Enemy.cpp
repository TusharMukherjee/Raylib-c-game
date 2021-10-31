#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture){
        worldPos = pos;
        texture = idle_texture;
        idle = idle_texture;
        run = run_texture;
        speed = 3.5f;

        width = texture.width/maxFrame;
        height = texture.height;
        // we don't want the enemy at center so doesnt copied with character 
}

void Enemy::tick(float deltaTime){

    if(!getAlive()){
        return;
    }
    // to target
    velocity = Vector2Subtract(target->getScreenPos() /* knight screenPos*/, getScreenPos() /* enemy screenPos*/);
    if(Vector2Length(velocity) < radius){
        velocity = {};
    }
    

    // we already done this code and using it as a child from basecharacter -----------------------------------------------------------------------------------------------------
    
    // to normalize for direction
    // toTarget = Vector2Normalize(toTarget);
    // // multiply by some speed constant 
    // toTarget = Vector2Scale(toTarget, speed);
    // // move enemy to worldPos update worldPos
    // worldPos = Vector2Add(worldPos /* enemys worldPos */, toTarget /* target normalize direction which scaled by speed till worldPos of target reached */);
    // screenPos = Vector2Subtract(worldPos, target->getWorldPos());
    
    BaseCharacter::tick(deltaTime); // if never changed the function then call the base function like this
    // // same enemy will going to do as character -----------------------------------------------------START
    // worldPosLastFrame = worldPos;

    // // update animation character-------------------------------------------------------------------
    // // float dT{GetFrameTime()};

    // runningTime += deltaTime;
    // if (runningTime >= updateTime)
    // {
    //     frame++;
    //     runningTime = 0.f;
    //     if (frame > maxFrame)
    //         frame = 0;
    // }

    // // draw the character -----------------------------------------------------------------
    // Rectangle source{frame * width, 0.f, rightleft * width, height};
    // Rectangle dest{screenPos.x, screenPos.y, 4.0f * width, 4.0f * height};
    // Vector2 origin{};
    // DrawTexturePro(texture, source, dest, origin, 0.f, WHITE);

    // // same enemy will going to do as character -----------------------------------------------------END

    if(CheckCollisionRecs(target->getCollisionRec(), getCollisionRec())){
        target->takeDamage(damagePerSecond * deltaTime); // if enemy collides with knight then knight take damage
    }
}

Vector2 Enemy::getScreenPos(){
    return Vector2Subtract(worldPos, target->getWorldPos());
}

// void Enemy::undoMovement(){
//     worldPos = worldPosLastFrame;
// }

// Rectangle Enemy::getCollisionRec(){
//     return Rectangle{
//         screenPos.x,
//         screenPos.y,
//         width * 4.f,
//         height * 4.f
//     };
// }