// bool CellClass::Spread_Tiberium(bool forced) (0x00478A40)
// Westwood's CellClass::Spread_Tiberium: unless forced, only when the ore may
// spread from here (unknown_478950); the cell's tiberium (the first one when
// forced on a cell without) is planted in the first neighbour, from a random
// facing on, where it may germinate (TerrainClass 0x006E40B6, 0x006E984F).
#include "shared/cell.hpp"
#include "shared/overlay.hpp"
#include "shared/tiberium.hpp"
#include "shared/id_source.hpp"
// @ref ?unknown_47c3a0@CellClass@@QAE_NHH@Z=0047c3a0

bool CellClass::Spread_Tiberium(bool forced)
{
    if (!forced) {
        if (!unknown_478950()) {
            return false;
        }
    }
    int overlay = OverlayIndex;
    int tiberium = OverlayClass::To_Tiberium(overlay);
    if (!forced && tiberium == -1) {
        return false;
    }
    if (tiberium == -1) {
        tiberium = 0;
    }
    TiberiumClass *type = unknown_TiberiumClass_list_00ac0b30[tiberium];
    int offset = Random_Pick(0, 7);
    int count = 8;
    for (int index = 0; index < count; index++) {
        int facing = (index + offset) & 7;
        CellClass *cell = &Adjacent_Cell(facing);
        if (cell != 0 && cell->Can_Tiberium_Germinate(type)) {
            int amount = 3;
            return cell->unknown_47c3a0(tiberium, amount);
        }
    }
    return false;
}
