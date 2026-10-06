#pragma once
#include "raylib.h"
#include "sprite.h"
#include "world.h"
#include "tile_registry.h"
#include "item_registry.h"
#include "texture_manager.h"
#include "constants.h"
#include <string_view>
#include <vector>

struct ItemData {
	int itemId;
	int count;
	int durability = 1;
	bool isHeld = false;
};

class Player {
public:
	Player();
	~Player();

	Vector2 pos;
	Vector2 direction;
	float speed = 1000.0f;

	float velocity_y = 0.0f;
	float gravity = 20000.0f;  // the gravity system is retarded but it works so dont touch it
	const float jump_strength = -1500.0f;
	bool is_grounded = false;

	float mine_range = 7.0f;

	int left_tile;
	int right_tile;
	int top_tile;
	int bot_tile;

	World *world = nullptr;
	TileRegistry *tile_reg = nullptr;
	ItemRegistry *item_reg = nullptr;
	TMan *tman = nullptr;
	Camera2D *cam = nullptr;

	float tile_size = 16.0f;

	Sprite sprite;

private:
	std::vector<ItemData> inventory{40};

public:
	bool inventoryState = false;
	std::vector<Rectangle> slot_rectangles;
	ItemData heldItem{0, 0, 0, false};
	ItemData buffer{0, 0, 0, false};

	void Draw();
	void Input();
	void DrawInventory();
	int GetClickedSlot();
	void ClearHeldItem();
	void CalcInvUIPoints();
	void SetInventorySlot(int index, ItemData data);
	void Mine();
	ItemData &GetInventorySlot(int index);
	void Move(float dt);
	bool Collision(std::string_view types);
	void Update(float dt);
};
