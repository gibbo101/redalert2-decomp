// int FootClass::unknown_slot86(int *damage, int distance, WarheadTypeClass *warhead, TechnoClass *source, bool forced, int arg6) (0x004C6000)
// Damage: a Sonic warhead shakes off a riding parasite (and its source
// stops attacking); a parasite resets its timer by the damage beyond the
// SuppressionThreshold, or to 50 frames when healed; then TechnoClass's
// damage. The team hears of a hit; a Whiner team of a computer house calls
// for help, and a unit hit in a mission that allows it (but not one that
// forbids) gives up its order (slot 261).
#include "shared/foot.hpp"
#include "shared/house.hpp"
#include "shared/parasite.hpp"
#include "shared/team_type.hpp"
#include "shared/techno_type.hpp"
#include "shared/warhead_type.hpp"
// @ref ?Unknown_00607440@ParasiteClass@@QAEXXZ=00607440
// @ref ?unknown_slot86@TechnoClass@@UAEHPAHHPAVWarheadTypeClass@@PAV1@_NH@Z=006cdc40
// @ref ?Unknown_006B9AA0@TeamClass@@QAEXPAVFootClass@@HPAVTechnoClass@@@Z=006b9aa0
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?unknown_6d3400@TechnoClass@@QAEXPAV1@@Z=006d3400
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref ?Frame@@3HA=00a40d2c

int FootClass::unknown_slot86(int *damage, int distance, WarheadTypeClass *warhead, TechnoClass *source, bool forced, int arg6)
{
    if (warhead->Sonic && unknown_580 != 0) {
        unknown_580->unknown_588->Unknown_00607440();
        if (source != 0) {
            source->unknown_slot220(0);
        }
    }
    if (unknown_580 != 0 && source != unknown_580 && *damage > unknown_580->unknown_slot32()->SuppressionThreshold) {
        unknown_580->unknown_588->unknown_2c = CDTimerClass<FrameTimerClass>(*damage * 2 - unknown_580->unknown_slot32()->SuppressionThreshold);
    }
    if (unknown_580 != 0 && *damage < 0) {
        unknown_580->unknown_588->unknown_2c = CDTimerClass<FrameTimerClass>(50);
        unknown_580->unknown_588->Unknown_00607440();
    }
    int result = TechnoClass::unknown_slot86(damage, distance, warhead, source, forced, arg6);
    if (result == 5) {
        return result;
    }
    if (result != 0 && Team != 0) {
        Team->Unknown_006B9AA0(this, result, source);
        return result;
    }
    if (result != 4 && result != 0) {
        if (Team != 0 && Team->Class->Whiner && !House->Unknown_004F52F0()) {
            if (source == 0) {
                return result;
            }
            unknown_6d3400(source);
        }
        if (source != 0 && Control()->unknown_04 && !Control()->unknown_05) {
            unknown_slot261(0, true);
        }
    }
    return result;
}
