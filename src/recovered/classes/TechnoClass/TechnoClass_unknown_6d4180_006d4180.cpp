// bool TechnoClass::unknown_6d4180() (0x006D4180)
// Whether the object may take another order now (hypothesis: should keep
// guarding / hunting): false for a while after being constructed or
// asked; a team member of an aggressive, non-suicide team on mission 2
// without a target always may; otherwise it needs 0x006D40C0, and a unit
// on mission 2 of a type with BalloonHover, or on mission 5 whose
// weapon (flag +0x126) already is the one for the target, may not.
#include "shared/techno.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
// @ref ?Frame@@3HA=00a40d2c
// @ref ?unknown_ac01cc@@3IA=00ac01cc
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?unknown_6d40c0@TechnoClass@@QAE_NXZ=006d40c0
// @ref ?unknown_613b60@UnknownTechno408@@QAEHXZ=00613b60

bool TechnoClass::unknown_6d4180()
{
    if ((unsigned int)(Frame - unknown_3f4) < unknown_ac01cc) {
        return false;
    }
    bool foot;
    bool foot2;
    if (unknown_228 == 0 && !House->Unknown_004F52F0() && this != 0) {
        if (this != 0) foot = AbstractFlags.IsFoot;
        if (foot && ((FootClass *)this)->Team != 0) {
            TeamTypeClass *team_type = ((FootClass *)this)->Team->Class;
            if (!team_type->Suicide && team_type->Aggressive && Mission == 2) {
                return true;
            }
        }
    }
    if (!unknown_6d40c0()) {
        return false;
    }
    if (Mission == 2 && unknown_slot32()->BalloonHover) {
        foot2 = false;
        if (this != 0) foot2 = AbstractFlags.IsFoot;
        if (!foot2) {
            return false;
        }
        if (((FootClass *)this)->unknown_494 == unknown_slot105()) {
            if (unknown_408 == 0) {
                return true;
            }
            if (unknown_408->unknown_613b60() <= 0) {
                return true;
            }
        }
    }
    if (!unknown_slot32()->OpportunityFire) {
        if (Mission != 5) {
            return false;
        }
        int weapon = unknown_slot226();
        WeaponStruct *slot = unknown_slot231(weapon);
        bool flagged;
        if (slot == 0 || slot->WeaponType == 0 || !slot->WeaponType->unknown_126) {
            flagged = false;
        } else {
            flagged = true;
        }
        int best = unknown_slot174(unknown_228);
        bool same = best == weapon;
        if (flagged && same) {
            return false;
        }
    }
    return true;
}
