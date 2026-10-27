// void TechnoClass::unknown_slot262(bool arg1, bool arg2, bool arg3, HouseClass *house) (0x006D5C30, slot 262)
// Like slot 70, but records the sight for slot 263: when the object has
// sight (+0x32D) and the owner is not MultiplayPassive, the height level
// (Z / LeptonsPerSightIncrease, times 10) is kept in +0x378 (rising clears
// arg1), the radius is Sight scaled by 1 + level/100 and VeteranSight; the
// first time (+0x1E4 clear) it stores the coordinate and radius in +0x1E8 /
// +0x1F4 and reveals for house (when arg3 asks) or the owner, later only
// for house when arg3 asks.
#include "shared/techno.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Map@@3VMapClass@@A=008324e0
// @ref ?Sight_From@MapClass@@QAEXABUCoordStruct@@HPAVHouseClass@@_N2H2H@Z=0054a110
// @ref __real@8@3ff8a3d70a3d70a3d800=0079c518
// @ref __real@8@3fff8000000000000000=0079a708
// @ref __real@8@00000000000000000000=0079b610

void TechnoClass::unknown_slot262(bool arg1, bool arg2, bool arg3, HouseClass *house)
{
    if (!unknown_32d || House->Type->MultiplayPassive) {
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
    if (!unknown_1e4) {
        unknown_1e4 = true;
        unknown_1e8 = Coord;
        unknown_1f4 = sight;
        if (sight != 0) {
            if (arg3 && house != 0) {
                Map.Sight_From(CoordStruct(Coord), sight, house, arg1, arg2, 0, true, 0);
            } else {
                Map.Sight_From(CoordStruct(Coord), sight, House, arg1, arg2, 0, true, 0);
            }
        }
    } else if (arg3 && sight != 0 && house != 0) {
        Map.Sight_From(CoordStruct(Coord), sight, house, arg1, arg2, 0, true, 0);
    }
}
