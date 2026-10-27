// bool CellClass::unknown_47b9c0() const (0x0047B9C0): whether the cell's
// tile is the one at 0x00A52C60 or in the 16-tile set at 0x00A52590.
#include "shared/cell.hpp"
// @ref ?unknown_tileset_a52c60@@3HA=00a52c60
// @ref ?unknown_tileset_a52590@@3HA=00a52590

bool CellClass::unknown_47b9c0() const
{
    if (IsoTileIndex != unknown_tileset_a52c60 && (IsoTileIndex < unknown_tileset_a52590 || IsoTileIndex >= unknown_tileset_a52590 + 16)) {
        return false;
    }
    return true;
}
