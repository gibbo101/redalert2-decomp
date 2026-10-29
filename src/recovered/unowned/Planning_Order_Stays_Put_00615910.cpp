#define RA2_COORD_EQUAL_MEMBER
// bool __fastcall Planning_Order_Stays_Put(TechnoClass *techno, int mission, TargetClass target) (0x00615910)
// Whether a mission 11 order leaves the techno where it is: no target, or a
// target cell (a cell, or the cell of a techno) that is the techno's own
// slot 104 cell. Name hypothesis.
#include "shared/planning.hpp"
#include "shared/cell.hpp"

bool __fastcall Planning_Order_Stays_Put(TechnoClass *techno, int mission, TargetClass target)
{
    if (mission == 11) {
        if (!target.Kind) {
            return true;
        }
        if (techno != 0) {
            Cell here = techno->unknown_slot104();
            Cell cell = techno->unknown_slot104();
            CellClass *target_cell = target.As_Cell();
            if (target_cell != 0) {
                cell = target_cell->MapCoords;
            } else {
                TechnoClass *target_techno = target.As_Techno();
                if (target_techno != 0) {
                    cell = target_techno->unknown_slot104();
                }
            }
            if (here == cell) {
                return true;
            }
        }
    }
    return false;
}
