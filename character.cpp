#include"character.h"
#include"raymath.h"

Character::Character(int winWidth, int winHeight) :
    windowWidth(winWidth), windowHeight(winHeight) 
{
    width = texture.width/maxFrame;
    height = texture.height;
        
}

Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.0f - 4.0f * (0.5f * width),        // (float) tpecasting like this is with C and it typecast without knowing the datatype it is casting
        static_cast<float>(windowHeight) / 2.0f - 4.0f * (0.5f * height)    // static_cast<float> variablename is a c++ predefined function which typecast from which datatype it is typecasting
    };
} 

// void Character::setScreenPos(int winWidth, int winHeight)
// {
    
// }



void Character::tick(float deltaTime)
{ 
    if(!getAlive())
    {
        return;
    }
    // worldPosLastFrame = worldPos;

    // Vector2 velocity{};
    if (IsKeyDown(KEY_UP))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_DOWN))
        velocity.y += 1.0;
    if (IsKeyDown(KEY_LEFT))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_RIGHT))
        velocity.x += 1.0;

        // basecharacter called after update velocity than cover to 0.

    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if(rightleft > 0.f){
        origin = {0.f, weapon.height * 4.f};
        offset = {35.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * 4.f,
            weapon.width * 4.f,
            weapon.width * 4.f
        };
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 35.f : rotation = 0.f;
    }
    else{
        origin = {weapon.width * 4.f, weapon.height * 4.f};
        offset = {25.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * 4.f,
            getScreenPos().y + offset.y - weapon.height * 4.f,
            weapon.width * 4.f,
            weapon.width * 4.f
        };
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -35.f : rotation = 0.f;
    }

    // draw the sword

    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width)*rightleft, static_cast<float>(weapon.height)};
    Rectangle dest{ getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width*4.f, weapon.height*4.f };
    DrawTexturePro(weapon, source, dest, origin, rotation , WHITE);
    // DrawRectangleLines(
    //     weaponCollisionRec.x, weaponCollisionRec.y, weaponCollisionRec.width, weaponCollisionRec.height, RED
    // );

    // update animation character-------------------------------------------------------------------
    // float dT{GetFrameTime()};

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
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if(health <= 0.f)
    {
        setAlive(false);
    }
}

// void Character::undoMovement(){
//     worldPos = worldPosLastFrame;
// }

// Rectangle Character::getCollisionRec(){
//     return Rectangle{
//         screenPos.x,
//         screenPos.y,
//         width * 4.f,
//         height * 4.f
//     };
// }