// int CellClass::Get_Tiberium_Value() const (0x0047A230): the credit value
// of the cell's ore: its tiberium type's value times (OverlayData + 1); 0
// when the overlay is not ore.
#include "shared/cell.hpp"
#include "shared/overlay.hpp"
#include "shared/tiberium.hpp"

int CellClass::Get_Tiberium_Value() const
{
    int tiberium = OverlayClass::To_Tiberium(OverlayIndex);
    if (tiberium == -1) {
        return 0;
    }
    return unknown_TiberiumClass_list_00ac0b30[tiberium]->Value * (OverlayData + 1);
}
