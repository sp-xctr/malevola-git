#pragma once
#include <vector>

struct TileDef {
    const char* textureKey;
    bool isSolid;
    int dropItemId;
};

class TileRegistry {
public:
    void Register(int id, TileDef td);
    TileDef &Get(int id) { return defs[id]; };

private:
    std::vector<TileDef> defs;
};
