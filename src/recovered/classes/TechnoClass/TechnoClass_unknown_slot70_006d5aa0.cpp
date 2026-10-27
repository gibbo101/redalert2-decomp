// void TechnoClass::unknown_slot70(bool arg1, bool arg2) (0x006D5AA0, slot 70)
// Reveals the map around the object (0x00549C50) when it has sight (+0x32D),
// except for a MultiplayPassive owner outside game mode 0. The height level
// (Z / LeptonsPerSightIncrease, times 10) is kept in +0x378; rising above the
// last level clears arg1. The radius is the type's Sight scaled by
// 1 + level/100, times VeteranSight for a veteran or elite with the sight
// ability when that factor is set.
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_00549C50@MapClass@@QAEXABUCoordStruct@@HPAVHouseClass@@_N2222@Z=00549c50
// @ref ?unknown_7133a0@UnknownTechnoPair@@QBE_NXZ=007133a0
// @ref ?unknown_713420@UnknownTechnoPair@@QBE_NXZ=00713420
// @ref __real@8@3ff8a3d70a3d70a3d800=0079c518
// @ref __real@8@3fff8000000000000000=0079a708
// @ref __real@8@00000000000000000000=0079b610

extern int unknown_game_mode_a3d298;    // 0x00A3D298

void TechnoClass::unknown_slot70(bool arg1, bool arg2)
{
    if (!unknown_32d) {
        return;
    }
    if (House->Type->MultiplayPassive && unknown_game_mode_a3d298 != 0) {
        return;
    }
    int level = CoordStruct(Coord).Z / Rules->unknown_1324 * 10;
    if (level > unknown_378) {
        arg1 = false;
    }
    unknown_378 = level;
    int sight = (int)(unknown_slot32()->Sight * (unknown_378 * 0.01 + 1.0));
    if (unknown_118.unknown_7133a0() || unknown_118.unknown_713420()) {
        TechnoTypeClass *type = unknown_slot32();
        if ((unknown_118.unknown_7133a0() && type->VeteranAbilities.Ability[5])
            || (unknown_118.unknown_713420() && (type->VeteranAbilities.Ability[5] || type->EliteAbilities.Ability[5]))) {
            if (Rules->unknown_5a0 != 0.0) {
                sight = (int)(sight * Rules->unknown_5a0);
            }
        }
    }
    if (sight != 0) {
        Map.Unknown_00549C50(CoordStruct(Coord), sight, House, arg1, arg2, false, true, true);
    }
}
