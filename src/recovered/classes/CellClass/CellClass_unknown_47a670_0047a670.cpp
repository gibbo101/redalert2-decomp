// bool CellClass::unknown_47a670() const (0x0047A670): whether veins may
// spread into the cell (hypothesis; OverlayClass 0x005DC180 and
// VeinholeMonsterClass 0x00710BB0 ask it): the cell's +0x11C is below 5, its
// land type is not 2, 3, 8 or 6, it has no overlay or a vein overlay, and
// each cardinal neighbour likewise (a neighbour with +0x11C above 4 refuses
// while this cell's +0x11C is 0, unless it holds veins).
#include "shared/cell.hpp"
#include "shared/overlay_type.hpp"
// @ref ?OverlayTypes@@3V?$DynamicVectorClass@PAVOverlayTypeClass@@@@A=00a35de8

bool CellClass::unknown_47a670() const
{
    if (unknown_11c <= 4 && unknown_ec != 2 && unknown_ec != 3 && unknown_ec != 8 && unknown_ec != 6
        && (OverlayIndex == -1 || OverlayTypes[OverlayIndex]->IsVeins)) {
        for (int facing = 0; facing < 8; facing += 2) {
            CellClass const &cell = ((CellClass *)this)->Adjacent_Cell(facing);
            if ((cell.unknown_11c > 4 && unknown_11c == 0 && (cell.OverlayIndex == -1 || !OverlayTypes[cell.OverlayIndex]->IsVeins))
                || cell.unknown_ec == 2 || cell.unknown_ec == 3 || cell.unknown_ec == 8 || cell.unknown_ec == 6
                || (cell.OverlayIndex != -1 && !OverlayTypes[cell.OverlayIndex]->IsVeins)) {
                return false;
            }
        }
        return true;
    }
    return false;
}
