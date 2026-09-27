#include "world.h"
#include "constants.h"
#include <cassert>

int World::GetTile(int x, int y) {
    assert(x < width && y < height && x >= 0 && y >= 0);
    return tiles[x + y * width];
}

void World::SetTile(int x, int y, int tile) {
    assert(x < width && y < height && x >= 0 && y >= 0);
    tiles[x + y * width] = tile;
}

void World::GenerateWorld() {
    for (int x{}; x < width; x++) {
        for (int y{}; y < height; y++) {
            if (y > 360) {
                World::SetTile(x, y, T_DIRT);
            } else {
                World::SetTile(x, y, T_AIR);
            } // work on world gen and add blocks + items
        }
    }
}

/*
1. Tile & world foundation

Tile grid data structure, tile IDs, tile size
Camera-relative rendering (only draw visible tiles)
Basic world gen: flat/rolling terrain, single biome (Forest)
Save/load for the tile array — do this now, not later, since retrofitting it
after the world format gets complex is painful

2. Player + tile collision

Tile-based collision (not freeform hitbox collision)
Mining (swap tile to air) and placing (swap air to tile)
Basic inventory (slot array, item IDs, stack counts)

3. Data-driven item/tile definitions

Before adding more content, build the system that lets you define items/tiles as
data instead of hardcoded logic This unlocks fast iteration for everything below
— skipping this is the #1 way solo devs stall out

4. Crafting

Recipe lookup against inventory
One crafting station (workbench) — more stations come later, same system

5. Ore tiers + depth-based world gen

Add ore generation by depth (Copper → Iron → Gold, pick your own naming)
Requires world gen to be revisited — expected, this always happens iteratively

6. Basic enemy framework

Generic entity: health, hitbox, simple AI state (idle/chase/attack)
One or two early enemy types using this framework, not bespoke code each

7. Combat

Player attack (melee first — simplest to implement and test)
Damage numbers, knockback, enemy death/drops

8. NPC + housing

Housing validation (enclosed space, light, door)
One NPC vendor as proof of concept

9. Boss framework

Reusable AI state machine: attack patterns, phase transitions on health
thresholds This is a system, not a boss — build it generic before boss #1

10. Boss #1

Simplest boss you can design (something like "flies at player, occasional dash")
to validate the framework end-to-end

11. Progression gating

Boss #1 drops something that unlocks new ore/gear/area
Confirms your data-driven item system (step 3) actually scales

12. Second biome

Reuses world gen (step 1/5) with new tile/ore set — good test that your systems
generalize

13. Ranged/Magic weapon classes

Add once melee (step 7) works — these usually need a projectile system, which
melee doesn't

14. Accessories / armor set bonuses

Layer onto existing item system (step 3) — shouldn't require new architecture if
step 3 was done right

15. Boss #2, #3...

Now that the framework (step 9) exists, each new boss is mostly content, not new
engineering

16. Events, evil-biome spread, Hardmode-style content doubling

These are advanced/optional — only tackle if the above is solid and you still
have energy
*/
