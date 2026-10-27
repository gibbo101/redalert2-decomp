// int FootClass::unknown_slot101(int arg1, int arg2, int arg3, int arg4, int arg5) (0x004C86E0)
// Whether the unit may enter cell arg1 (hypothesis: Can_Enter_Cell): with a
// locomotor and arg5 set, the locomotor's answer for the cell's position
// (ILocomotion::Can_Enter_Cell); otherwise 0.
#include "shared/foot.hpp"
// @ref __com_issue_error@4=00795940

int FootClass::unknown_slot101(int arg1, int arg2, int arg3, int arg4, int arg5)
{
    if (Locomotor != 0 && (char)arg5) {
        Cell cell = ((UnknownCellClass *)arg1)->unknown_24;
        return Locomotor.Checked()->Can_Enter_Cell(cell);
    }
    return 0;
}
