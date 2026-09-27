#pragma once
#include <raylib.h>

class Sprite {
public:
	Texture2D *image = nullptr;
	Rectangle rect;
	Rectangle hitbox;

	float hw_offset = 0.4f;
	float hh_offset = 0.75f;
	float h_posx_offset = 0.3f;
	float h_posy_offset = 0.26f;

	void SetUp(Texture2D* t);
	void Update(Vector2* pos);
	void Draw(Vector2 *v);
};
