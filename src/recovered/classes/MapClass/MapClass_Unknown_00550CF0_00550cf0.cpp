// bool MapClass::Unknown_00550CF0(Cell const &cell, int width, int height, int speed, int arg5, int arg6, int arg7, bool arg8, bool no_overlay) (0x00550CF0)
// Whether every cell of the width x height block at a cell (of the global
// Map) can be entered (CellClass 0x00478760 with speed and the other
// movement arguments) and, with no_overlay, has no overlay.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8
// @ref ?Unknown_00478760@CellClass@@QAE_NH_N0HHH0@Z=00478760

bool MapClass::Unknown_00550CF0(Cell const &cell, int width, int height, int speed, int arg5, int arg6, int arg7, bool arg8, bool no_overlay)
{
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            CellClass &object = Map[Cell(cell.X + x, cell.Y + y)];
            if (no_overlay && object.OverlayIndex != -1) {
                return false;
            }
            if (!object.Unknown_00478760(speed, false, false, arg5, arg6, arg7, arg8)) {
                return false;
            }
        }
    }
    return true;
}
