// bool CellClass::unknown_4789d0() (0x004789D0): grows the cell's ore one
// stage through unknown_47c3a0 when unknown_4788e0's conditions hold (they
// are tested inline again); false otherwise.
#include "shared/cell.hpp"
#include "shared/overlay.hpp"
#include "shared/tiberium.hpp"
#include "shared/id_source.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref __real@8@3feea7c5ac471b478800=0079c520
// @ref ?unknown_47c3a0@CellClass@@QAE_NH_N@Z=0047c3a0

bool CellClass::unknown_4789d0()
{
    if (unknown_id_source_a3d290->unknown_222a) {
        int tiberium = OverlayClass::To_Tiberium(OverlayIndex);
        if (tiberium != -1) {
            TiberiumClass *type = unknown_TiberiumClass_list_00ac0b30[tiberium];
            if (!unknown_11c && OverlayData < type->unknown_e4 - 1 && !(type->unknown_b0 < 0.00001)) {
                int type_index = OverlayClass::To_Tiberium(OverlayIndex);
                return unknown_47c3a0(type_index, true);
            }
        }
    }
    return false;
}
