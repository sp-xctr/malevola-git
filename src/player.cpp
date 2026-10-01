#include "player.h"
#include "constants.h"
#include "item_registry.h"
#include "raylib.h"
#include "raymath.h"
#include "tile_registry.h"
#include <cassert>
#include <string_view>

Player::Player() {
    pos.x = 100 * tile_size;
    pos.y = 350 * tile_size;
}

Player::~Player() = default;

void Player::Draw() { sprite.Draw(&pos); }

void Player::Input() {
    direction.x = 0;

    if (IsKeyDown(KEY_D)) {
        direction.x = 1;
    }
    if (IsKeyDown(KEY_A)) {
        direction.x = -1;
    }
    if (IsKeyPressed(KEY_TAB)) {
        if (inventoryState) {
            inventoryState = false;
        } else { inventoryState = true; }
    }
    if (inventoryState && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !heldItem.isHeld) {
        int clickedSlot = GetClickedSlot();

        heldItem = GetInventorySlot(clickedSlot);
        if (heldItem.itemId != I_NONE) {
            heldItem.isHeld = true;
            SetInventorySlot(clickedSlot, {I_NONE, 0, 0, false});
        }
    }
    else if (inventoryState && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && heldItem.isHeld) {
        int clickedSlot = GetClickedSlot();
        ItemData *clicked_inventory_slot = &GetInventorySlot(clickedSlot);

        if (heldItem.itemId != clicked_inventory_slot->itemId) {
            buffer = GetInventorySlot(clickedSlot);
            SetInventorySlot(clickedSlot, {heldItem.itemId, heldItem.count, heldItem.durability, false});
            heldItem = buffer;
        } else if (heldItem.itemId == clicked_inventory_slot->itemId) {
            clicked_inventory_slot->count += heldItem.count;
            ClearHeldItem();
        }

    }
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Mine(); // also handling if the block is solid logic
    }
}

bool Player::Collision(std::string_view type) {
    Rectangle *h = &sprite.hitbox;

    int x, y, tileId;

    if (type == "vertical") {
        if (velocity_y >= 0) {
            // bottom side
            int b1 = (int) ((h->y + h->height));
            x = ((h->x + h->width / 2) / tile_size);
            y = b1 / tile_size;
            tileId = world->GetTile(x, y);

            if (tile_reg->Get(tileId).isSolid) {
                if (b1 > y * tile_size) {
                    pos.y = (y * tile_size) - h->height - (h->height * sprite.h_posy_offset);
                    velocity_y = 0;
                    return true;
                }
            }
        }
        if (velocity_y < 0) {
            // top side
            int t1 = (int) (h->y);
            x = ((h->x + h->width / 2) / tile_size);
            y = (t1 / tile_size);
            tileId = world->GetTile(x, y);

            if (tile_reg->Get(tileId).isSolid) {
                if (t1 < y * tile_size) {
                    pos.y = ((y + 1) * tile_size) - (h->height * sprite.h_posy_offset);;
                    velocity_y = 0;
                }
            }
        }
    }
    if (type == "horizontal") {
        if (direction.x > 0) {
            // right side
            int r1 = (int) (h->x + h->width);
            x = (r1 / tile_size);
            y = (h->y + (h->height / 2)) / tile_size;
            tileId = world->GetTile(x, y);

            if (tile_reg->Get(tileId).isSolid) {
                if (r1 > x * tile_size) {
                    pos.x = (x * tile_size) - h->width - (h->width * sprite.h_posx_offset);
                }
            }
        }
        if (direction.x < 0) {
            // left side
            int l1 = (int) (h->x);
            x = (l1 / tile_size);
            y = (h->y + (h->height / 2)) / tile_size;
            tileId = world->GetTile(x, y);

            if (tile_reg->Get(tileId).isSolid) {
                if (l1 < x * tile_size) {
                    pos.x = ((x + 1) * tile_size) - (h->width * sprite.h_posx_offset);
                }
            }
        }
    }
    return false;
}

void Player::Mine() {
    Vector2 mouse_pos = GetMousePosition();
    Vector2 world_pos = GetScreenToWorld2D(mouse_pos, *cam);

    float dist = Vector2Distance(pos, world_pos);
    if (dist / tile_size > mine_range) { return; }

    int tile_x = (int) (world_pos.x / tile_size);
    int tile_y = (int) (world_pos.y / tile_size);

    if (tile_reg->Get((world->GetTile(tile_x, tile_y))).isSolid) {
        world->SetTile(tile_x, tile_y, T_AIR);
    };
}

int Player::GetClickedSlot() {
    int index = 0;
    Vector2 mouse_pos = GetMousePosition();

    for (int i{}; i < slot_rectangles.size(); i++) {
        if (CheckCollisionPointRec(mouse_pos, slot_rectangles[i])) {
            index = i;
            break;
        }
    }
    return index;
}

void Player::SetInventorySlot(int index, ItemData data) {
    assert(index <= inventory.size());
    inventory[index] = data;
}

ItemData &Player::GetInventorySlot(int index) {
    return inventory[index];
}

void Player::ClearHeldItem() {
    heldItem = {0, 0, 0, false};
}

// seed: 5421710019781524683

void Player::CalcInvUIPoints() {
    float size = 48.0f;

    for (int y = 1; y < 5; y++) {
        for (int x = 1; x < 11; x++) {
            slot_rectangles.push_back({(float) ((x * size) + x), (float) ((y * size) + y), size, size});
        }
    }
}

void Player::DrawInventory() {
    int index = 0;
    ItemData item;
    ItemDef itemdef;
    for (auto &rec: slot_rectangles) {
        DrawRectangleLines(rec.x, rec.y, rec.width, rec.height, Color{0, 0, 0, 255});
        item = GetInventorySlot(index);
        index += 1;
        if (item.itemId == I_NONE) {
            continue;
        }

        itemdef = item_reg->Get(item.itemId);
        DrawTexture(*tman->GetTexture(itemdef.iconKey), (int)rec.x, (int)rec.y, WHITE);
        DrawText(TextFormat("%d", item.count), (int)rec.x + 7, (int)rec.y + 7, 10, WHITE);
    }

    if (heldItem.isHeld) {
        itemdef = item_reg->Get(heldItem.itemId);
        Vector2 mp = GetMousePosition();
        DrawTexture(*tman->GetTexture(itemdef.iconKey), mp.x, mp.y, WHITE);
    }
}

void Player::Move(float dt) {
    direction = Vector2Normalize(direction);

    pos.x += direction.x * speed * dt;
    sprite.Update(&pos);
    Collision("horizontal");

    velocity_y += gravity * dt;
    pos.y += velocity_y * dt;
    sprite.Update(&pos);

    is_grounded = Collision("vertical");

    if (is_grounded) {
        velocity_y = 0.0f;
    }

    if (IsKeyPressed(KEY_SPACE) && is_grounded) {
        velocity_y = jump_strength;
        is_grounded = false;
    }
}

void Player::Update(float dt) {
    Input();

    Move(dt);
}
