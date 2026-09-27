#pragma once
#include <vector>
#include <string>

enum class Category {
    WEAPON,
    CONSUMABLE,
    EQUIPMENT,
    BLOCK,
};

struct ItemDef {
    std::string name;
    const char* iconKey;
    Category category;

    int durability = 0;
    int maxStack = 9999;
    int damage = 0;
};

class ItemRegistry{
public:
    void Register(int itemId, ItemDef def);
    ItemDef &Get(int itemId) { return items[itemId]; };

private:
    std::vector<ItemDef> items;
};
