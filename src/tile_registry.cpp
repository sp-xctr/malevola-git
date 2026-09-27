#include "tile_registry.h"

void TileRegistry::Register(int id, TileDef td) {
    if (id >= (int)defs.size()) {
        defs.resize(id + 1);
    }
    defs[id] = td;
}
