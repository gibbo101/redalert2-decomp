// void MapClass::Destroy_Low_Bridge_Span(Cell const &cell) (0x00556BF0)
// Tiberian Sun's Repair_Low_Bridge_Span shape: for a low bridge overlay, finds
// the span's end cell next to `cell` (through the low bridge test 0x00562930)
// and destroys the EW or NS span from there. The differences are
// TPoint2D<short>::operator- (the last one is the Map unit's out-of-line copy
// 0x0056AA40) and operator+.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
// @ref ??G?$TPoint2D@F@@QBE?BV0@ABV0@@Z=0056aa40
// @ref ?Destroy_Low_Bridge_EW@MapClass@@QAEXABVCell@@@Z=005576a0
// @ref ?Destroy_Low_Bridge_NS@MapClass@@QAEXABVCell@@@Z=005579c0

void MapClass::Destroy_Low_Bridge_Span(Cell const &cell)
{
    int overlay = Map[cell].OverlayIndex;

    if (overlay >= 0x4a && overlay <= 0x52 || overlay >= 0x5c && overlay <= 0x5f || overlay == 0x64) {
        if (!Unknown_00562930(cell - Cell(0, 1))) {
            Destroy_Low_Bridge_EW(cell + Cell(0, 1));
        } else {
            if (!Unknown_00562930(cell - Cell(0, 2))) {
                Destroy_Low_Bridge_EW(cell);
            } else {
                Destroy_Low_Bridge_EW(cell - Cell(0, 1));
            }
        }
    } else if (overlay >= 0x53 && overlay <= 0x5b || overlay >= 0x60 && overlay <= 0x63 || overlay == 0x65) {
        if (!Unknown_00562930(cell - Cell(1, 0))) {
            Destroy_Low_Bridge_NS(cell + Cell(1, 0));
        } else {
            if (!Unknown_00562930(cell - Cell(2, 0))) {
                Destroy_Low_Bridge_NS(cell);
            } else {
                Destroy_Low_Bridge_NS(cell - Cell(1, 0));
            }
        }
    }
}
