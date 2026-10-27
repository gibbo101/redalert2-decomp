// void CellClass::Set_House_Bit(int house) (0x0047C320).
#include "shared/cell.hpp"

void CellClass::Set_House_Bit(int house)
{
    unknown_78 |= 1 << house;
}
