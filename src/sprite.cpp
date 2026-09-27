#include "sprite.h"

void Sprite::Draw(Vector2 *pos) {
	DrawTextureRec(*image, rect, *pos, WHITE);

	DrawRectangleLines(hitbox.x, hitbox.y, hitbox.width, hitbox.height, Color{ 255, 255, 0, 255 });
}

void Sprite::Update(Vector2* pos) {
	hitbox.x = pos->x + (image->width * h_posx_offset);
	hitbox.y = pos->y + (image->height * h_posy_offset);
}

void Sprite::SetUp(Texture2D* t) {
	image = t;
	rect = Rectangle{ 0, 0, (float)image->width, (float)image->height };
	hitbox = Rectangle{ 0, 0, (float)image->width * hw_offset, (float)image->height * hh_offset };
}
