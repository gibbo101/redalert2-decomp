// int CellClass::Get_Tiberium_Type() const (0x0047A220): the tiberium type of
// the cell's overlay (OverlayClass::To_Tiberium; -1 when it is not ore).
#include "shared/cell.hpp"
#include "shared/overlay.hpp"

int CellClass::Get_Tiberium_Type() const
{
    return OverlayClass::To_Tiberium(OverlayIndex);
}
