// void CellClass::Clear_House_Bit(int house) (0x0047C340).
#include "shared/cell.hpp"

void CellClass::Clear_House_Bit(int house)
{
    unknown_78 &= ~(1 << house);
}
