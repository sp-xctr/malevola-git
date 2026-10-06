#include "game.h"
#include "item_registry.h"
#include "raylib.h"
#include "constants.h"
#include <algorithm>

Game::Game() {}

void Game::Init() {
    // SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(1600, 900, "Malevola raylib");

    screen_width = GetScreenWidth();
    screen_height = GetScreenHeight();

    tm.Walk();

    RegAllTiles();
    RegAllItems();

    player.sprite.SetUp(tm.GetTexture("player-idle"));
    player.CalcInvUIPoints();

    camera.target = player.pos;
    camera.offset = {screen_width / 2.0f, screen_height / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;

    world.GenerateWorld();

    player.world = &world;
    player.tile_reg = &tile_reg;
    player.item_reg = &item_reg;
    player.tman = &tm;
    player.cam = &camera;
    world.tile_reg = &tile_reg;
}

void Game::GeneralUpdate() {
    dt = GetFrameTime();

    if (IsKeyPressed(KEY_F11)) {
        ToggleFullscreen();
    }
}

void Game::StartedUpdate() {
    player.Update(dt * 0.1f);
    camera.target.x = player.pos.x + player.sprite.image->width / 2;
    camera.target.y = player.pos.y;
    Game::VisibleRangeCalc(&vr);
}

void Game::RegAllTiles() {
    tile_reg.Register(T_NONE, {"none", false, 0});
    tile_reg.Register(T_AIR, {"tile-air", false, 0});
    tile_reg.Register(T_DIRT, {"tile-dirt", true, I_DIRT});
    tile_reg.Register(T_STONE, {"tile-stone", true, I_STONE});
}

void Game::RegAllItems() {
    item_reg.Register(I_NONE, {"nonius nonais vais lais", "verygoodkey", Category::WEAPON, 9999, 0, 4444});
    item_reg.Register(I_DIRT, {"dirt", "icon-dirt", Category::BLOCK});
    item_reg.Register(I_STONE, {"stone", "icon-stone", Category::BLOCK});
}

void Game::StartedDraw() {
    BeginMode2D(camera);

    for (int x = vr.startX; x <= vr.endX; x++) {
        for (int y = vr.startY; y <= vr.endY; y++) {
            int tileId = world.GetTile(x, y);

            Texture2D tex = *tm.GetTexture(tile_reg.Get(tileId).textureKey);

            DrawTexture(tex, x * tile_size, y * tile_size, WHITE);
        }
    }

    player.Draw();

    EndMode2D();

    if (player.inventoryState) {
        player.DrawInventory();
    }
}

void Game::VisibleRangeCalc(VisibleRange *vr) {
    vr->startX = ((camera.target.x - camera.offset.x) / tile_size) - screen_buf;
    vr->startX = std::clamp(vr->startX, 0, world_width - 1);

    vr->endX = (vr->startX + (screen_width / tile_size)) + screen_buf;
    vr->endX = std::clamp(vr->endX, 0, world_width - 1);

    vr->startY = ((camera.target.y - camera.offset.y) / tile_size) - screen_buf;
    vr->startY = std::clamp(vr->startY, 0, world_height - 1);

    vr->endY = (vr->startY + (screen_height / tile_size)) + screen_buf;
    vr->endY = std::clamp(vr->endY, 0, world_height - 1);
}

void Game::Shutdown() { CloseWindow(); }
