// Runs infantry status, missions, reactions and animation updates (0x00502D20).
#include "shared/infantry.hpp"
#include "shared/anim.hpp"
#include "shared/techno_map.hpp"
#include "shared/rules.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Frame@@3HA=00a40d2c
// @ref ??0AnimClass@@QAE@PAVAnimTypeClass@@ABUCoordStruct@@HHHH@Z=00420110
// @ref ??2@YAPAXI@Z=00782017
// @ref ?AI@FootClass@@UAEXXZ=004c8ff0
// @ref ?unknown_5025c0@InfantryClass@@QAEXXZ=005025c0
// @ref ?unknown_507170@InfantryClass@@QAE_NXZ=00507170
// @ref ?Update_Fire_00507530@InfantryClass@@QAEXXZ=00507530
// @ref ?Advance_Animation_005078b0@InfantryClass@@QAEXXZ=005078b0
// @ref ?Update_Movement_00507b90@InfantryClass@@QAEXXZ=00507b90
// @ref ?unknown_506f30@InfantryClass@@QAEXXZ=00506f30
// @ref ?unknown_invalid_coord_a410f8@@3UCoordStruct@@A=00a410f8
// @ref ?unknown_44d880@BuildingClass@@QAE_NXZ=0044d880
inline CoordStruct Infantry_Damage_Animation_Coord(CoordStruct const &coord)
{
    CoordStruct where = coord;
    where.X += 120;
    where.Y += 120;
    return where;
}
void InfantryClass::AI()
{
    if (unknown_574 >= 0) {
        unknown_5025c0();
        unknown_slot267(false);
        return;
    }
    if ((unknown_slot111() || unknown_slot112()) && Frame % 24 == 0 && Rules->unknown_2a8 != 0) {
        new AnimClass(Rules->unknown_2a8, Infantry_Damage_Animation_Coord(Coord), 0, 1, 0x600, 0);
    }
    if (unknown_20c != 0) {
        unknown_20c->AI();
    }
    if (unknown_slot112() || (unknown_slot111() && unknown_210)) {
        Locomotor.Checked()->Process();
    }
    if (unknown_slot111()) {
        if (unknown_228 != 0) {
            unknown_slot220(0);
        }
        if (unknown_494 != 0) {
            unknown_slot260(0, 1);
        }
        return;
    }
    if (unknown_slot122()) {
        if (unknown_slot91() == -1 && MissionQueue == -1) {
            unknown_slot261(false, true);
        }
        unknown_slot117();
    }
    if (Strength <= 0 && !Is_Busy_Sequence_00509710(Sequence)) {
        Strength = 1;
    }
    FootClass::AI();
    if (!unknown_7d) {
        return;
    }
    if (unknown_slot91() == 5 || unknown_slot91() == 11) {
        CoordStruct coord = Coord;
        BuildingClass *building = Map_Cell(coord)->Unknown_004717B0();
        if (building != 0 && !building->Type->InvisibleInGame) {
            if (building->Type->LaserFence) {
                if (building->unknown_4ec != 12 && building->unknown_4ec != 8) {
                    goto scatter;
                }
            } else if (building->Type->FirestormWall) {
                if (!building->House->unknown_142) {
                    goto scatter_done;
                }
                goto scatter;
            } else if (!building->Type->Gate || !building->unknown_44d880()) {
            scatter:
                unknown_slot87(unknown_invalid_coord_a410f8, true, true);
            }
        }
    }
scatter_done:
    if (unknown_slot29() != 2) {
        unknown_slot71(2);
    }
    if (unknown_57d && AnimationStage.unknown_10 == 0) {
        unknown_57d = false;
        if (unknown_5090d0()) {
            unknown_slot311(28, false, false);
        } else {
            unknown_slot311(0, false, false);
        }
    }
    if (unknown_5070e0()) {
        return;
    }
    if (unknown_507170()) {
        return;
    }
    if (unknown_slot122()) {
        if (unknown_slot91() == -1 && MissionQueue == -1) {
            unknown_slot261(false, true);
        }
        unknown_slot117();
    }
    unknown_506f30();
    if (unknown_494 == 0 && !unknown_5c3 && unknown_5c2 && unknown_5b0.Value() == 0) {
        unknown_5c2 = false;
    }
    Update_Fire_00507530();
    if (unknown_7d) {
        Advance_Animation_005078b0();
        if (unknown_7d) {
            Update_Movement_00507b90();
        }
    }
}
