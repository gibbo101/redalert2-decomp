// wchar_t const *CellClass::unknown_47a200() const (0x0047A200): the UI name
// of the cell's tiberium; null when the overlay is not ore.
#include "shared/cell.hpp"
#include "shared/overlay.hpp"
#include "shared/tiberium.hpp"

wchar_t const *CellClass::unknown_47a200() const
{
    int tiberium = OverlayClass::To_Tiberium(OverlayIndex);
    if (tiberium != -1) {
        return unknown_TiberiumClass_list_00ac0b30[tiberium]->UIName;
    }
    return 0;
}
