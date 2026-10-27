// bool CellClass::unknown_47b590() const (0x0047B590): whether the cell has
// no tile (IsoTileIndex 0xFFFF or 0).
#include "shared/cell.hpp"

bool CellClass::unknown_47b590() const
{
    if (IsoTileIndex == 0xFFFF || IsoTileIndex == 0) {
        return true;
    }
    return false;
}
