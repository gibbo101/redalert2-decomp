// bool CellClass::unknown_4788e0() const (0x004788E0): whether the cell's ore
// may grow (hypothesis): growth is on in the scenario (+0x222A), the overlay is
// ore, +0x11C is clear, the ore is below its last stage and its type's growth
// rate (+0xB0) is not below 0.00001.
#include "shared/cell.hpp"
#include "shared/overlay.hpp"
#include "shared/tiberium.hpp"
#include "shared/id_source.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref __real@8@3feea7c5ac471b478800=0079c520

bool CellClass::unknown_4788e0() const
{
    if (!unknown_id_source_a3d290->unknown_222a) {
        return false;
    }
    int tiberium = OverlayClass::To_Tiberium(OverlayIndex);
    if (tiberium == -1) {
        return false;
    }
    TiberiumClass *type = unknown_TiberiumClass_list_00ac0b30[tiberium];
    if (unknown_11c) {
        return false;
    }
    if (OverlayData >= type->unknown_e4 - 1) {
        return false;
    }
    if (type->unknown_b0 < 0.00001) {
        return false;
    }
    return true;
}
