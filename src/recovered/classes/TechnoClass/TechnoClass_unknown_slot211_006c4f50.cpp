// bool TechnoClass::unknown_slot211(ObjectClass *target) (0x006C4F50, slot 211)
// Whether target is within the primary weapon's warhead spread (CellSpread
// minus CellInset) of this object, measured in cells.
#include "shared/techno.hpp"
#include "shared/foot.hpp"
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref __ftol=0077f110

bool TechnoClass::unknown_slot211(ObjectClass *target)
{
    if (unknown_slot225()) {
        WarheadTypeClass *warhead = unknown_slot229()->WeaponType->Warhead;
        if (warhead != 0) {
            float range = warhead->CellSpread;
            range -= warhead->CellInset;
            Cell here = Coord_Cell(Center_Coord());
            Cell there = Coord_Cell(target->Center_Coord());
            Cell delta = here - there;
            if ((short)Short_Length(delta.X, delta.Y) <= range) {
                return true;
            }
        }
    }
    return false;
}
