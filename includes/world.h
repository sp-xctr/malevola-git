#include <vector>
#include "tile_registry.h"

class World {
public:
	World(int width, int height)
		: width(width), height(height), tiles(width * height, 0)  {};

	const int width;
	const int height;
	const int world_size = width * height;

	TileRegistry *tile_reg = nullptr;

	int GetTile(int x, int y);
	void SetTile(int x, int y, int tile);
	void GenerateWorld();

private:
	std::vector<int> tiles;
};
