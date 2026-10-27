// bool TechnoClass::unknown_slot160() (0x006C9020)
// Whether the techno may uncloak now (hypothesis, the counterpart of slot
// 161): not while it should stay cloaked (slot 154 off, no rank ability 6,
// the owner's cell flag 0x0047C2C0 clear and +0x32A off), not in cloak
// state 2, while the +0x244 timer runs, while it may fire at its target
// (slot 213), while a non-building's stage +0x1BC is set, or while the
// +0x1D4 timer runs.
#include "shared/techno.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMapClass@@A=008324e0
// @ref ?unknown_47c2c0@UnknownCellClass@@QBE_NH@Z=0047c2c0

bool TechnoClass::unknown_slot160()
{
    if (!unknown_slot154()) {
        bool allowed = true;
        if (unknown_118.unknown_7133a0() || unknown_118.unknown_713420()) {
            TechnoTypeClass *type = unknown_slot32();
            if (unknown_118.unknown_7133a0() && type->VeteranAbilities.Ability[6]) {
                allowed = false;
            } else if (unknown_118.unknown_713420() && (type->VeteranAbilities.Ability[6] || type->EliteAbilities.Ability[6])) {
                allowed = false;
            }
        }
        if (allowed && !((UnknownCellClass *)&Map[Coord_Cell(Center_Coord())])->unknown_47c2c0(House->ArrayIndex)
            && !unknown_32a) {
            return false;
        }
    }
    if (unknown_1b8 == 2) {
        return false;
    }
    if (unknown_244.Value() != 0) {
        return false;
    }
    if (unknown_228 != 0 && unknown_slot213(unknown_228)) {
        return false;
    }
    if (Kind_Of() != 6 && unknown_1bc.Value != 0) {
        return false;
    }
    if (unknown_1d4.Value() != 0) {
        return false;
    }
    return true;
}
