// bool MapClass::Unknown_0055EDB0(Cell const &cell) (0x0055EDB0)
// Tiberian Sun's Damage_Low_Bridge for the second low bridge set: for its overlay, finds the span's
// centre next to `cell` (through the low bridge test 0x00562980) and damages the
// EW (0x0055F020) or NS (0x0055F540) span there; true when it gave way.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
// @ref ??G?$TPoint2D@F@@QBE?BV0@ABV0@@Z=0056aa40
// @ref ?Unknown_0055F020@MapClass@@QAE_NABVCell@@@Z=0055f020
// @ref ?Unknown_0055F540@MapClass@@QAE_NABVCell@@@Z=0055f540

bool MapClass::Unknown_0055EDB0(Cell const &cell)
{
    int overlay = Map[cell].OverlayIndex;

    if (overlay >= 0xcd && overlay <= 0xd5 || overlay >= 0xdf && overlay <= 0xe2 || overlay == 0xe7) {
        if (!Unknown_00562980(cell - Cell(0, 1))) {
            return Unknown_0055F020(cell + Cell(0, 1));
        } else {
            if (!Unknown_00562980(cell - Cell(0, 2))) {
                return Unknown_0055F020(cell);
            } else {
                return Unknown_0055F020(cell - Cell(0, 1));
            }
        }
    } else if (overlay >= 0xd6 && overlay <= 0xde || overlay >= 0xe3 && overlay <= 0xe6 || overlay == 0xe8) {
        if (!Unknown_00562980(cell - Cell(1, 0))) {
            return Unknown_0055F540(cell + Cell(1, 0));
        } else {
            if (!Unknown_00562980(cell - Cell(2, 0))) {
                return Unknown_0055F540(cell);
            } else {
                return Unknown_0055F540(cell - Cell(1, 0));
            }
        }
    }
    return false;
}
