// bool MapClass::Unknown_005686B0(Rect const &rect, int house) (0x005686B0)
// Whether a cell rectangle (of the global Map) is free for a house: no cell
// has terrain, the house's bit in +0xDC, an overlay, +0x4C or +0x11C set or
// a building, and its corners are inside the local map (0x0055A590).
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8
// @ref ?Cell_Terrain@CellClass@@QBEPAVObjectClass@@_N@Z=004717e0
// @ref ?unknown_4717b0@CellClass@@QBEPAVObjectClass@@XZ=004717b0
// @ref ?Unknown_0055A590@MapClass@@QAE_NABVRect@@_N@Z=0055a590

bool MapClass::Unknown_005686B0(Rect const &rect, int house)
{
    int bit = 1 << house;
    for (int x = rect.X; x < rect.X + rect.Width; x++) {
        for (int y = rect.Y; y < rect.Y + rect.Height; y++) {
            CellClass &cell = Map[Cell(x, y)];
            if (cell.Cell_Terrain() != 0) {
                return false;
            }
            if (bit & cell.unknown_dc) {
                return false;
            }
            if (cell.OverlayIndex != -1) {
                return false;
            }
            if (cell.unknown_4c != 0) {
                return false;
            }
            if (cell.unknown_11c) {
                return false;
            }
            if (cell.unknown_4717b0() != 0) {
                return false;
            }
        }
    }
    return Unknown_0055A590(rect, true);
}
