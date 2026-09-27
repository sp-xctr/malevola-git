#include "item_registry.h"

void ItemRegistry::Register(int itemId, ItemDef def)   {
    if (itemId >= items.size()) {
        items.resize(itemId + 1);
    }

    items[itemId] = def;
}
