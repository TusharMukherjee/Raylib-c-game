#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{

    const int winWidth{384};
    const int winHeight{384};

    InitWindow(winWidth, winHeight, "Classy Clash TM");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};

    Character knight{winWidth, winHeight};

    // Prop rock{Vector2{0.f, 0.f}, LoadTexture("nature_tileset/Rock.png")};

    Prop props[]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")},
    };

    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")
    };

    Enemy* enemies[]{&goblin, &slime};

    for(auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    // goblin.setTarget(&knight); // didnt defined knight at 023 got segmentation error
    // float speed{4.0};

    // Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    // Vector2 knightPos{
    //     (float)winWidth / 2.0f - 4.0f * (0.5f * (float)knight.width / 6.0f),
    //     (float)winHeight / 2.0f - 4.0f * (0.5f * (float)knight.height)};

    // Texture2D knightIdle = LoadTexture("characters/knight_idle_spritesheet.png");
    // Texture2D knightRun = LoadTexture("characters/knight_run_spritesheet.png");
    // float rightleft{1.f};

    // // animation variable ---------------------------------------------------
    // float runningTime{};
    // int frame{};
    // const int maxFrame{6};
    // const float updateTime{1.0f / 12.0f};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the map -----------------------------------------------------------------------
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        // rock.Render(knight.getWorldPos());

        for(auto prop : props){
            prop.Render(knight.getWorldPos());
        }

        if(!knight.getAlive()){ // if the knight is dead
            DrawText("Game Over",55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else{// of the knight is alive
            std::string knightHealth = "Health: ";
            knightHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightHealth.c_str(), 55.f, 45.f, 40, VIOLET);
        }

        knight.tick(GetFrameTime());

        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + winWidth > map.width * 4.0f ||
            knight.getWorldPos().y + winHeight > map.height * 4.0f){

                knight.undoMovement();

            }

            for(auto prop : props){
                if(CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec())){
                    knight.undoMovement(); // stop movement while collission
                }
            }

            // goblin.tick(GetFrameTime());
            for(auto enemy : enemies){
                enemy->tick(GetFrameTime());
            }

            if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                for(auto enemy : enemies){
                    if(CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec())){
                    enemy->setAlive(false);
                    }
                }
                
            }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}