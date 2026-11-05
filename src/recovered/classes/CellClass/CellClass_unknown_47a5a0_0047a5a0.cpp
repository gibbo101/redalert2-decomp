// int CellClass::unknown_47a5a0() (0x0047A5A0): one bit per cardinal
// neighbour (facings 0, 2, 4, 6) that holds veins: an IsVeins overlay (when
// the neighbour's +0x11C is set, only those) or overlay 0x7E with overlay
// data of at least 48 (name hypothesis).
#include "shared/cell.hpp"
#include "shared/overlay_type.hpp"
// @ref ?OverlayTypes@@3V?$DynamicVectorClass@PAVOverlayTypeClass@@@@A=00a35de8

int CellClass::unknown_47a5a0()
{
    int mask = 0;
    for (int index = 0; index < 4; index++) {
        CellClass const &cell = ((CellClass const *)this)->Adjacent_Cell(index << 1);
        bool connected=false;
        if(cell.OverlayIndex!=-1 && (cell.unknown_11c<=0 || OverlayTypes[cell.OverlayIndex]->IsVeins)) {
            connected=(cell.OverlayIndex!=126 && OverlayTypes[cell.OverlayIndex]->IsVeins)
                || (cell.OverlayIndex==126 && cell.OverlayData>=48);
        }
        if(connected) mask|=1<<index;
    }
    return mask;
}
