// bool TechnoClass::unknown_6d40c0() (0x006D40C0)
// Whether the techno may scan for a target now: the scan interval
// (0x00AC01CC) has passed since +0x3F4, slot 113 does not hold, the type
// CanPassiveAquire, a building type flagged +0x121E needs 0x004532F0, and
// it is armed (slot 163) without a busy +0x230 or an owner-controlled slot
// 193.
#include "shared/techno.hpp"
// @ref ?Frame@@3HA=00a40d2c
// @ref ?unknown_ac01cc@@3IA=00ac01cc
// @ref ?unknown_4532f0@BuildingClass@@QAEHXZ=004532f0
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0

bool TechnoClass::unknown_6d40c0()
{
    if ((unsigned)(Frame - unknown_3f4) >= unknown_ac01cc) {
        if (!unknown_slot113()) {
            if (unknown_slot32()->CanPassiveAquire) {
                if (Kind_Of() != 6 || !((UnknownTechnoBuildingType *)((BuildingClass *)this)->Type)->unknown_121e
                    || ((BuildingClass *)this)->unknown_4532f0() != 0) {
                    bool busy = unknown_230 != 0 && ((UnknownTechno230 *)unknown_230)->unknown_24 != 0;
                    if ((!unknown_slot193() || !House->Unknown_004F52F0()) && !busy && unknown_slot163()) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
