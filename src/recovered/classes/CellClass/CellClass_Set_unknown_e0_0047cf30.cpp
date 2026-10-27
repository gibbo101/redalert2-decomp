// bool CellClass::Set_unknown_e0(void *value) (0x0047CF30): clears +0xE0 for
// null; otherwise claims it unless another value holds it.
#include "shared/cell.hpp"

bool CellClass::Set_unknown_e0(void *value)
{
    if (value == 0) {
        unknown_e0 = 0;
        return true;
    }
    if (unknown_e0 != 0 && unknown_e0 != value) {
        return false;
    }
    unknown_e0 = value;
    return true;
}
