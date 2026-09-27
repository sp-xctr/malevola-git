#pragma once
#include "player.h"
#include "texture_manager.h"
#include "tile_registry.h"
#include "item_registry.h"
#include <raylib.h>

enum GAME_STATES { TITLE, STARTED, END };

struct VisibleRange {
    int startX;
    int endX;
    int startY;
    int endY;
};

class Game {
public:
    Game();

    float dt{};

    int game_state = STARTED;
    const int tile_size = 16;
    int screen_width;
    int screen_height;
    const int world_width = 4200;
    const int world_height = 1200;
    int screen_buf = 1;

    TileRegistry tile_reg;
    ItemRegistry item_reg;

    Player player;

    Camera2D camera;
    VisibleRange vr{0, 0, 0, 0};

    TMan tm;

    World world{world_width, world_height};

    void Init();
    void StartedDraw();
    void GeneralUpdate();
    void StartedUpdate();
    void RegAllTiles();
    void RegAllItems();
    void VisibleRangeCalc(VisibleRange *vr);
    void Shutdown();
};
