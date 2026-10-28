// bool TechnoClass::unknown_6d3b60(TechnoClass *source, int arg2) (0x006D3B60)
// Whether the object answers an attack by source (hypothesis: may
// retaliate): the type must allow it (CanRetaliate) and the mission's
// control (Retaliate), the source must be an enemy that can be hit, and the
// player's own units only fire back when Rules PlayerReturnFire allows or
// they are on a mission that does; arg2 is not read.
#include "shared/techno.hpp"
#include "shared/foot.hpp"
#include "shared/aircraft.hpp"
#include "shared/infantry_type.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/rules.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref ?Is_Ally@HouseClass@@QBE_NPBVTechnoClass@@@Z=004e5580
// @ref ?unknown_6c16f0@TechnoClass@@QAEHH@Z=006c16f0
// @ref ?unknown_6d7550@TechnoClass@@QAENPAVObjectClass@@ABUCoordStruct@@@Z=006d7550
// @ref _unknown_geometry_l=00ac0188
// @ref ?unknown_7133a0@UnknownTechnoPair@@QBE_NXZ=007133a0
// @ref ?unknown_713420@UnknownTechnoPair@@QBE_NXZ=00713420

bool TechnoClass::unknown_6d3b60(TechnoClass *source, int arg2)
{
    if (source == 0) {
        return false;
    }
    if (!unknown_slot32()->CanRetaliate) {
        return false;
    }
    if (unknown_230 != 0 && ((UnknownTechno230 *)unknown_230)->unknown_24 != 0) {
        return false;
    }
    if (SpawnManager != 0) {
        return false;
    }
    if (House->Unknown_004F52F0() && unknown_228 != 0) {
        return false;
    }
    if (!Control()->unknown_08) {
        return false;
    }
    if (House->Is_Ally(source)) {
        return false;
    }
    if (source->unknown_slot49(House)) {
        return false;
    }
    if (unknown_6c16f0(-1) <= 0) {
        return false;
    }
    if (!unknown_slot163()) {
        return false;
    }
    TechnoTypeClass *type = unknown_slot32();
    int weapon = unknown_slot174(source);
    int result = unknown_slot217(source, weapon);
    if (result == 5 || result == 6) {
        return false;
    }
    if (House->Unknown_004F52F0() && source->Kind_Of() == 6) {
        if (Kind_Of() == 15 && ((InfantryTypeClass *)type)->C4) {
            return false;
        }
        if (unknown_6d7910(14)) {
            return false;
        }
    }
    if (House->Unknown_004F52F0() && Kind_Of() == 1) {
        BuildingTypeClass *building = ((UnitClass *)this)->Type->DeploysInto;
        if (building != 0 && building->Artillary) {
            return false;
        }
    }
    if (House->Unknown_004F52F0() && !Rules->PlayerReturnFire && Kind_Of() != 6
        && Mission != 11 && Mission != 5 && Mission != 25) {
        return false;
    }
    bool foot;
    if (this != 0) {
        foot = unknown_14_bit2;
    }
    if (this != 0 && foot && ((FootClass *)this)->Team != 0 && ((FootClass *)this)->Team->Class->Suicide) {
        return false;
    }
    if (!House->Unknown_004F52F0()) {
        AbstractClass *target = unknown_228;
        bool techno;
        if (target != 0) {
            techno = target->unknown_14_bit1;
        }
        if (target != 0 && techno
            && unknown_6d7550((ObjectClass *)target, unknown_geometry_l) > unknown_6d7550((ObjectClass *)source, unknown_geometry_l)) {
            return false;
        }
    }
    bool foot2;
    if (this != 0) {
        foot2 = unknown_14_bit2;
    }
    if (this != 0 && foot2 && source == ((FootClass *)this)->unknown_580) {
        return false;
    }
    return true;
}
