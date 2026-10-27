// bool CellClass::Is_House_Bit(int house) const (0x0047C2C0).
#include "shared/cell.hpp"

bool CellClass::Is_House_Bit(int house) const
{
    return (unknown_78 & (1 << house)) != 0;
}
