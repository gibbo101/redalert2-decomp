// void FootClass::Detach(AbstractClass *target, bool all) (0x004C8460)
// Forgets an object that is going away: the team, the parasite riding this
// unit (it is told too), the next team member, the TechnoClass target at
// +0x1B0, the navigation target (kept while an Occupier still holds a live
// building it is occupying, or while the target stays visible to the
// owner), the pending order's object and every queued destination.
#include "shared/foot.hpp"
#include "shared/infantry.hpp"
#include "shared/parasite.hpp"
#include "shared/map_view.hpp"
// @ref ?Detach@TechnoClass@@UAEXPAVAbstractClass@@_N@Z=006d2d10
// @ref ?unknown_flag_a40d04@@3_NA=00a40d04
// @ref ?unknown_6d6e50@TechnoClass@@QAEXPAVAbstractClass@@@Z=006d6e50
// @ref ?unknown_47c2e0@UnknownCellClass@@QAE_NH@Z=0047c2e0

void FootClass::Detach(AbstractClass *target, bool all)
{
    TechnoClass::Detach(target, all);
    if (Team == target) {
        Team = 0;
    }
    if (unknown_580 == target && (unknown_580->Strength == 0 || !unknown_flag_a40d04)) {
        unknown_580 = 0;
    }
    if (unknown_580 != 0 && unknown_580->Strength > 0) {
        unknown_580->unknown_588->Detach(target, true);
    }
    if (target == this) {
        unknown_580 = 0;
    }
    if (unknown_4c8 == target && all && target != 0) {
        unknown_4c8 = ((FootClass *)unknown_4c8)->unknown_4c8;
    }
    if (unknown_1b0 == target) {
        unknown_6d6e50(0);
    }
    if (unknown_498 == target) {
        unknown_498 = 0;
    }
    if (unknown_494 == target) {
        bool forget = true;
        bool object;
        if (!all && target != 0) {
            object = target->AbstractFlags.IsTechno;
        }
        if (!all && target != 0 && object) {
            UnknownCellClass *cell = (UnknownCellClass *)&Map[target->Center_Coord()];
            if (cell->unknown_47c2e0(House->ArrayIndex)) {
                forget = false;
            }
        }
        if (unknown_slot91() == 8 && Kind_Of() == 15 && ((InfantryClass *)this)->Type->Occupier && unknown_494 != 0
            && unknown_494->AbstractFlags.IsObject && ((ObjectClass *)unknown_494)->unknown_7d && ((ObjectClass *)unknown_494)->Strength > 0) {
        } else if (forget) {
            unknown_490 = 0;
            unknown_494 = 0;
        }
    }
    if (unknown_4bc == target) {
        unknown_4cdb60();
    }
    for (int index = 0; index < unknown_49c.Count(); index++) {
        if (unknown_49c[index] == target) {
            unknown_49c.Delete(index);
            index--;
        }
    }
    for (index = 0; index < unknown_478.Count(); index++) {
        if (unknown_478[index] == target) {
            unknown_478.Delete(index);
            index--;
        }
    }
}
