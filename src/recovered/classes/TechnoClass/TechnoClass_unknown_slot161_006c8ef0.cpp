// bool TechnoClass::unknown_slot161() (0x006C8EF0)
// Whether the techno may cloak now (hypothesis: ability 6 is CLOAK): not
// while slot 154 or +0x32A holds unless slot 201, 202, 111 or 112 does, not
// for a veteran or elite whose rank abilities include it, and not in a cell
// flagged for the owner (0x0047C2C0).
#include "shared/techno.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMapClass@@A=008324e0
// @ref ?unknown_47c2c0@UnknownCellClass@@QBE_NH@Z=0047c2c0

bool TechnoClass::unknown_slot161()
{
    if (!(unknown_slot154() || unknown_32a) || unknown_slot201() || unknown_slot202() || unknown_slot111()
        || unknown_slot112()) {
        bool allowed = true;
        if (unknown_118.unknown_7133a0() || unknown_118.unknown_713420()) {
            TechnoTypeClass *type = unknown_slot32();
            if (unknown_118.unknown_7133a0() && type->VeteranAbilities.Ability[6]) {
                allowed = false;
            } else if (unknown_118.unknown_713420() && (type->VeteranAbilities.Ability[6] || type->EliteAbilities.Ability[6])) {
                allowed = false;
            }
        }
        if (allowed && !((UnknownCellClass *)&Map[Coord_Cell(Center_Coord())])->unknown_47c2c0(House->ArrayIndex)) {
            return true;
        }
    }
    return false;
}
