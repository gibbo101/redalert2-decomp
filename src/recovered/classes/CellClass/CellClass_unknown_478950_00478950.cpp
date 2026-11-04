// bool CellClass::unknown_478950() const (0x00478950): whether ore may spread
// from the cell (hypothesis): spreading is on in the scenario (bit 0x80 of its
// +0x000), the overlay is ore past half of ... (the overlay data is compared
// with the ore type's index / 2, as the original does), +0x11C is clear, the
// type's spread rate (+0xA0) is not below 0.00001 and nothing occupies the cell.
#include "shared/cell.hpp"
#include "shared/overlay.hpp"
#include "shared/tiberium.hpp"
#include "shared/id_source.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref __real@8@3feea7c5ac471b478800=0079c520

bool CellClass::unknown_478950() const
{
    if (!(unknown_id_source_a3d290->unknown_000 & 0x80)) {
        return false;
    }
    int tiberium = OverlayClass::To_Tiberium(OverlayIndex);
    if (tiberium == -1) {
        return false;
    }
    if (OverlayData <= tiberium / 2) {
        return false;
    }
    if (unknown_11c) {
        return false;
    }
    if (unknown_TiberiumClass_list_00ac0b30[tiberium]->unknown_a0 < 0.00001) {
        return false;
    }
    if (OccupierPtr != 0) {
        return false;
    }
    return true;
}
