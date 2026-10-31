// void MapClass::Repair_Low_Bridge2_Span(Cell const &cell) (0x00561340)
// Tiberian Sun's Repair_Low_Bridge_Span for the second low bridge set (name a hypothesis): for a low bridge overlay, finds
// the span's end cell next to `cell` (through the low bridge test 0x00562980) and
// rebuilds the EW (0x00561F60) or NS (0x00562450) span from there; as Destroy_Low_Bridge_Span
// the last NS step is the Map unit's out-of-line TPoint2D<short>::operator- 0x0056AA40.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
// @ref ??G?$TPoint2D@F@@QBE?BV0@ABV0@@Z=0056aa40
// @ref ?Repair_Low_Bridge2_EW@MapClass@@QAEXABVCell@@@Z=00561f60
// @ref ?Repair_Low_Bridge2_NS@MapClass@@QAEXABVCell@@@Z=00562450

void MapClass::Repair_Low_Bridge2_Span(Cell const &cell)
{
    int overlay = Map[cell].OverlayIndex;

    if (overlay >= 0xcd && overlay <= 0xd5 || overlay >= 0xdf && overlay <= 0xe2 || overlay == 0xe7) {
        if (!Unknown_00562980(cell - Cell(0, 1))) {
            Repair_Low_Bridge2_EW(cell + Cell(0, 1));
        } else {
            if (!Unknown_00562980(cell - Cell(0, 2))) {
                Repair_Low_Bridge2_EW(cell);
            } else {
                Repair_Low_Bridge2_EW(cell - Cell(0, 1));
            }
        }
    } else if (overlay >= 0xd6 && overlay <= 0xde || overlay >= 0xe3 && overlay <= 0xe6 || overlay == 0xe8) {
        if (!Unknown_00562980(cell - Cell(1, 0))) {
            Repair_Low_Bridge2_NS(cell + Cell(1, 0));
        } else {
            if (!Unknown_00562980(cell - Cell(2, 0))) {
                Repair_Low_Bridge2_NS(cell);
            } else {
                Repair_Low_Bridge2_NS(cell - Cell(1, 0));
            }
        }
    }
}
