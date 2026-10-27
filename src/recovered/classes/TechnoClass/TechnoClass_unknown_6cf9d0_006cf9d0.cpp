// int TechnoClass::unknown_6cf9d0() (0x006CF9D0)
// How many of the three neighbouring cells (facings 4, 2 and 3) hold one
// of the cliff or column tiles (tile set 0x00A52C74, positions 7-16); 0
// unless a bridge applies under the object (0x006CF670 or 0x006CF820).
#include "shared/techno.hpp"
#include "shared/gscreen.hpp"
#include "shared/foot.hpp"
#include "shared/techno_map.hpp"
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70

extern Cell const AdjacentCell[8];
// @ref ?unknown_tileset_a52c74@@3HA=00a52c74
// @ref ?unknown_6cf670@TechnoClass@@QAE_NXZ=006cf670
// @ref ?unknown_6cf820@TechnoClass@@QAE_NXZ=006cf820

extern int unknown_tileset_a52c74;

int TechnoClass::unknown_6cf9d0()
{
    Cell position = unknown_slot104();
    int count = 0;
    UnknownCellClass *here = (UnknownCellClass *)&Map[position];
    if (here != 0 && (unknown_6cf670() || unknown_6cf820())) {
        UnknownCellClass *south = (UnknownCellClass *)&Map[(AdjacentCell[4] + position)];
        UnknownCellClass *east = (UnknownCellClass *)&Map[(AdjacentCell[2] + position)];
        UnknownCellClass *west = (UnknownCellClass *)&Map[(AdjacentCell[3] + position)];
        if (south != 0 && east != 0 && west != 0) {
            int tile = south->unknown_38;
            if (tile != 0xFFFF && tile != 0xFF) {
                if (tile - unknown_tileset_a52c74 + 1 >= 7 && tile - unknown_tileset_a52c74 + 1 <= 16) {
                    count = 1;
                }
            }
            tile = east->unknown_38;
            if (tile != 0xFFFF && tile != 0xFF) {
                if (tile - unknown_tileset_a52c74 + 1 >= 7 && tile - unknown_tileset_a52c74 + 1 <= 16) {
                    count = 1;
                }
            }
            tile = west->unknown_38;
            if (tile != 0xFFFF && tile != 0xFF) {
                if (tile - unknown_tileset_a52c74 + 1 >= 7 && tile - unknown_tileset_a52c74 + 1 <= 16) {
                    count = count + 1;
                }
            }
        }
    }
    return count;
}
