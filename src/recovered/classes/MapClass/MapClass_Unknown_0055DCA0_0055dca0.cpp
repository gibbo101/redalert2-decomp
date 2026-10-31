// bool MapClass::Unknown_0055DCA0(Cell const &cell) (0x0055DCA0)
// Tiberian Sun's Damage_Low_Bridge: for a low bridge overlay, finds the span's
// centre next to `cell` (through the low bridge test 0x00562930) and damages the
// EW (0x0055DEF0) or NS (0x0055E410) span there; true when it gave way.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
// @ref ??G?$TPoint2D@F@@QBE?BV0@ABV0@@Z=0056aa40
// @ref ?Unknown_0055DEF0@MapClass@@QAE_NABVCell@@@Z=0055def0
// @ref ?Unknown_0055E410@MapClass@@QAE_NABVCell@@@Z=0055e410

bool MapClass::Unknown_0055DCA0(Cell const &cell)
{
    int overlay = Map[cell].OverlayIndex;

    if (overlay >= 0x4a && overlay <= 0x52 || overlay >= 0x5c && overlay <= 0x5f || overlay == 0x64) {
        if (!Unknown_00562930(cell - Cell(0, 1))) {
            return Unknown_0055DEF0(cell + Cell(0, 1));
        } else {
            if (!Unknown_00562930(cell - Cell(0, 2))) {
                return Unknown_0055DEF0(cell);
            } else {
                return Unknown_0055DEF0(cell - Cell(0, 1));
            }
        }
    } else if (overlay >= 0x53 && overlay <= 0x5b || overlay >= 0x60 && overlay <= 0x63 || overlay == 0x65) {
        if (!Unknown_00562930(cell - Cell(1, 0))) {
            return Unknown_0055E410(cell + Cell(1, 0));
        } else {
            if (!Unknown_00562930(cell - Cell(2, 0))) {
                return Unknown_0055E410(cell);
            } else {
                return Unknown_0055E410(cell - Cell(1, 0));
            }
        }
    }
    return false;
}
