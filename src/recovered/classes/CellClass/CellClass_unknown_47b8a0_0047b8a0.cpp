// bool CellClass::unknown_47b8a0() const (0x0047B8A0): whether the cell's
// tile is in the sets at 0x00A6CB6C (11), 0x00A6E014 (24) or 0x00A52EFC (66).
#include "shared/cell.hpp"
// @ref ?unknown_tileset_a6cb6c@@3HA=00a6cb6c
// @ref ?unknown_tileset_a6e014@@3HA=00a6e014
// @ref ?unknown_tileset_a52efc@@3HA=00a52efc

bool CellClass::unknown_47b8a0() const
{
    if ((IsoTileIndex < unknown_tileset_a6cb6c || IsoTileIndex >= unknown_tileset_a6cb6c + 11)
        && (IsoTileIndex < unknown_tileset_a6e014 || IsoTileIndex >= unknown_tileset_a6e014 + 24)
        && (IsoTileIndex < unknown_tileset_a52efc || IsoTileIndex >= unknown_tileset_a52efc + 66)) {
        return false;
    }
    return true;
}
