// bool __fastcall Unknown_0055AF60(int tile) (0x0055AF60)
// Whether a tile index is one of the 42 tiles of the set starting at
// 0x00A6CB74.
#include "shared/map.hpp"
// @ref ?unknown_tileset_a6cb74@@3HA=00a6cb74

bool __fastcall Unknown_0055AF60(int tile)
{
    if (tile >= unknown_tileset_a6cb74 && tile < unknown_tileset_a6cb74 + 42) {
        return true;
    }
    return false;
}
