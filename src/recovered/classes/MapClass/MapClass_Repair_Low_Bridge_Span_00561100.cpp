// void MapClass::Repair_Low_Bridge_Span(Cell const &cell) (0x00561100)
// Tiberian Sun's Repair_Low_Bridge_Span (name a hypothesis): for a low bridge overlay, finds
// the span's end cell next to `cell` (through the low bridge test 0x00562930) and
// rebuilds the EW (0x005615A0) or NS (0x00561A80) span from there; as Destroy_Low_Bridge_Span
// the last NS step is the Map unit's out-of-line TPoint2D<short>::operator- 0x0056AA40.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
// @ref ??G?$TPoint2D@F@@QBE?BV0@ABV0@@Z=0056aa40
// @ref ?Repair_Low_Bridge_EW@MapClass@@QAEXABVCell@@@Z=005615a0
// @ref ?Repair_Low_Bridge_NS@MapClass@@QAEXABVCell@@@Z=00561a80

void MapClass::Repair_Low_Bridge_Span(Cell const &cell)
{
    int overlay = Map[cell].OverlayIndex;

    if (overlay >= 0x4a && overlay <= 0x52 || overlay >= 0x5c && overlay <= 0x5f || overlay == 0x64) {
        if (!Unknown_00562930(cell - Cell(0, 1))) {
            Repair_Low_Bridge_EW(cell + Cell(0, 1));
        } else {
            if (!Unknown_00562930(cell - Cell(0, 2))) {
                Repair_Low_Bridge_EW(cell);
            } else {
                Repair_Low_Bridge_EW(cell - Cell(0, 1));
            }
        }
    } else if (overlay >= 0x53 && overlay <= 0x5b || overlay >= 0x60 && overlay <= 0x63 || overlay == 0x65) {
        if (!Unknown_00562930(cell - Cell(1, 0))) {
            Repair_Low_Bridge_NS(cell + Cell(1, 0));
        } else {
            if (!Unknown_00562930(cell - Cell(2, 0))) {
                Repair_Low_Bridge_NS(cell);
            } else {
                Repair_Low_Bridge_NS(cell - Cell(1, 0));
            }
        }
    }
}
