// bool CellClass::unknown_slot20() const (0x0047B9F0, slot 20): false when
// the cell's tile is in the 14-tile set at 0x00A52580, else true.
#include "shared/cell.hpp"
// @ref ?unknown_tileset_a52580@@3HA=00a52580

bool CellClass::unknown_slot20() const
{
    if (IsoTileIndex >= unknown_tileset_a52580 && IsoTileIndex < unknown_tileset_a52580 + 14) {
        return false;
    }
    return true;
}
