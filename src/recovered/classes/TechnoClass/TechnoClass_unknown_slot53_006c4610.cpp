// bool TechnoClass::unknown_slot53(CoordStruct const *coord, int dir) (0x006C4610, slot 53)
// Puts the techno on the map at coord facing dir (the low byte, as a
// 256-step direction): +0x32D records whether the cell is on the map
// (0x0055A660), then ObjectClass slot 53. An active object then: slot 262,
// sight (0x0054A550 out to +0x1F4 + 3), joins the 0x008322E0 list for
// BombSight types, the owner's 0x004ED610, both facings (the turret pointed
// back by the type's FireAngle), +0x3EC/+0x3F0, slot 261 (with +0x190 set
// for infantry), slot 117 when slot 122 says so, the height level (+0x378),
// +0x373 cleared off the map, the cell's slot 168 weight (+0x400), the map
// position at +0x1A0, and the owner's +0x130 when +0x114 is unset.
#include "shared/techno.hpp"
#include "shared/rules.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_0055A660@MapClass@@QAE_NABVCell@@_N@Z=0055a660
// @ref ?Unknown_0054A550@MapClass@@QAEXABUCoordStruct@@HHH@Z=0054a550
// @ref ?Unknown_00631BA0@RadarClass@@QAE?AUPoint2D@@ABUCoordStruct@@_N@Z=00631ba0
// @ref ?unknown_slot53@ObjectClass@@UAE_NPBUCoordStruct@@H@Z=005d3890
// @ref ?unknown_list_8322e0@@3VUnknownList8322E0@@A=008322e0
// @ref ?Unknown_00436680@UnknownList8322E0@@QAEXPAVTechnoClass@@@Z=00436680
// @ref ?Unknown_004ED610@HouseClass@@QAEXPAVTechnoClass@@_N@Z=004ed610
// @ref ?unknown_476b20@UnknownCellClass@@QAEXHH@Z=00476b20

bool TechnoClass::unknown_slot53(CoordStruct const *coord, int dir)
{
    unknown_32d = Map.Unknown_0055A660(Coord_Cell(*coord), true);
    if (ObjectClass::unknown_slot53(coord, dir)) {
        if (!unknown_7d) {
            return true;
        }
        unknown_slot262(0, 0, 0, 0);
        Map.Unknown_0054A550(CoordStruct(Coord), 0, unknown_1f4 + 3, 0);
        if (unknown_slot32()->BombSight != 0) {
            unknown_list_8322e0.Unknown_00436680(this);
        }
        House->Unknown_004ED610(this, false);
        unknown_2e0.Set_Current(UnknownFacingDir((unsigned short)((unsigned char)dir << 8)));
        unknown_2c8.Set_Current(UnknownFacingDir(0x4000));
        {
            UnknownFacingDir fire = UnknownFacingDir((unsigned short)(0x4000 - ((unsigned char)unknown_slot32()->FireAngle << 8)));
            unknown_2c8.Set_Desired(fire);
        }
        unknown_3ec = 1;
        unknown_3f0 = 0;
        if (Kind_Of() == 15) {
            unknown_190 = true;
        }
        unknown_slot261(true, true);
        unknown_190 = false;
        if (unknown_slot122()) {
            unknown_slot117();
        }
        unknown_378 = (char)(coord->Z / Rules->unknown_1324) * 10;
        if (!Map.Unknown_0055A660(Coord_Cell(*coord), true)) {
            unknown_373 = false;
        }
        UnknownCellClass *here = (UnknownCellClass *)unknown_slot105();
        if (here != 0) {
            unknown_400 = unknown_slot168();
            here->unknown_476b20(Owner(), unknown_400);
        }
        unknown_1a0 = Map.Unknown_00631BA0(CoordStruct(Coord), true);
        if (unknown_114 == -1) {
            unknown_114 = House->unknown_130;
        }
        return true;
    }
    return false;
}
