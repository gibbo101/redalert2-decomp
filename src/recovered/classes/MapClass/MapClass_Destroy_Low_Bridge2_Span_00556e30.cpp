// void MapClass::Destroy_Low_Bridge2_Span(Cell const &cell) (0x00556E30)
// Tiberian Sun's Repair_Low_Bridge_Span shape for the second low bridge set: for its overlay, finds
// the span's end cell next to `cell` (through the low bridge test 0x00562980)
// and destroys the EW or NS span from there. The differences are
// TPoint2D<short>::operator- (the last one is the Map unit's out-of-line copy
// 0x0056AA40) and operator+.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
// @ref ??G?$TPoint2D@F@@QBE?BV0@ABV0@@Z=0056aa40
// @ref ?Destroy_Low_Bridge2_EW@MapClass@@QAEXABVCell@@@Z=00557ce0
// @ref ?Destroy_Low_Bridge2_NS@MapClass@@QAEXABVCell@@@Z=00558010

void MapClass::Destroy_Low_Bridge2_Span(Cell const &cell)
{
    int overlay = Map[cell].OverlayIndex;

    if (overlay >= 0xcd && overlay <= 0xd5 || overlay >= 0xdf && overlay <= 0xe2 || overlay == 0xe7) {
        if (!Unknown_00562980(cell - Cell(0, 1))) {
            Destroy_Low_Bridge2_EW(cell + Cell(0, 1));
        } else {
            if (!Unknown_00562980(cell - Cell(0, 2))) {
                Destroy_Low_Bridge2_EW(cell);
            } else {
                Destroy_Low_Bridge2_EW(cell - Cell(0, 1));
            }
        }
    } else if (overlay >= 0xd6 && overlay <= 0xde || overlay >= 0xe3 && overlay <= 0xe6 || overlay == 0xe8) {
        if (!Unknown_00562980(cell - Cell(1, 0))) {
            Destroy_Low_Bridge2_NS(cell + Cell(1, 0));
        } else {
            if (!Unknown_00562980(cell - Cell(2, 0))) {
                Destroy_Low_Bridge2_NS(cell);
            } else {
                Destroy_Low_Bridge2_NS(cell - Cell(1, 0));
            }
        }
    }
}
