// void VeinholeMonsterClass::unknown_func_710ff0() (0x00710FF0)
// Spreads the veins: takes one to four nodes (random) with the lowest keys
// off the heap and grows the vein at each node's cell (0x00712300).
// Body: 646 bytes (ret at 0x00711275); the inventory splits it at 0x00711076.
#include "shared/veinhole.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/random.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref ?unknown_func_712300@VeinholeMonsterClass@@QAEXPAVCellClass@@@Z=00712300

void VeinholeMonsterClass::unknown_func_710ff0()
{
    if (unknown_9c == 0) {
        return;
    }
    int count = 0;
    int steps = abs(unknown_id_source_a3d290->Random()()) % 4 + 1;
    UnknownVeinNode *node = unknown_9c->Remove_Min();
    while (count < steps && node != 0) {
        unknown_func_712300(&Map[Map[node->Position].MapCoords]);
        count++;
        if (count >= steps) {
            break;
        }
        node = unknown_9c->Remove_Min();
    }
}
