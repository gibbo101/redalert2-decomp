// bool CellClass::unknown_47c200() (0x0047C200): true when the map refuses
// the cell (Map.Unknown_0055A740(this, true) fails); otherwise false when its
// tile type's +0x2D5 flag is clear, when +0x11C or flags 0x500 of +0x140 are
// set, or when a building or terrain object occupies it.
#include "shared/cell.hpp"
// @ref ?unknown_flag_a40958@@3_NA=00a40958
#include "shared/map_cell_view.hpp"

bool CellClass::unknown_47c200()
{
    if (!Map.Unknown_0055A740(this, true)) {
        return true;
    }
    if ((IsoTileIndex >= 0 && IsoTileIndex < IsoTileTypes.Count() && !IsoTileTypes[IsoTileIndex]->unknown_2d5)
        || unknown_11c || (unknown_140 & 0x500) != 0) {
        return false;
    }
    if (unknown_4717b0() != 0) {
        return false;
    }
    if (Cell_Terrain() != 0) {
        return false;
    }
    return true;
}
