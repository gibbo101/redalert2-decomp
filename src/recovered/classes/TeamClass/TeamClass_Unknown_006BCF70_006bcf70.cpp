// BuildingClass *__fastcall Unknown_006BCF70(BuildingTypeClass *type, HouseClass *enemy, FootClass *member, int mode, bool enemy_only) (0x006BCF70)
// The building of a type that rates best by mode (0 lowest and 1 highest house value of its cell's
// block, 2 nearest and 3 farthest from the member) among enemy's buildings and those of houses the
// member's house is not allied with (or passive ones): enemy's best when it beats the overall best,
// else the overall best unless enemy_only.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/house.hpp"
#include "shared/map_view.hpp"
#include "shared/coord_distance.hpp"
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref __ftol=0077f110
// @ref ?unknown_BuildingClass_list_00a40af8@@3V?$DynamicVectorClass@PAVBuildingClass@@@@A=00a40af8
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540

AbstractClass *__fastcall Unknown_006BCF70(BuildingTypeClass *type, HouseClass *enemy, FootClass *member, int mode, bool enemy_only)
{
    BuildingClass *enemy_best = 0;
    BuildingClass *best = 0;
    int enemy_best_value = -1;
    int best_value = -1;
    for (int index = 0; index < unknown_BuildingClass_list_00a40af8.Count(); index++) {
        BuildingClass *building = unknown_BuildingClass_list_00a40af8[index];
        bool is_enemy = building->House == enemy;
        if (building->Type == type
            && (is_enemy || !member->House->Is_Ally(building->House) || building->House->Type->MultiplayPassive)) {
            int value = -1;
            switch (mode) {
            case 0: {
                Cell cell = Coord_Cell(building->Center_Coord());
                value = 0x7FFFFFFF - Map.Unknown_0054E3A0(cell, member->House);
                break;
            }
            case 1: {
                Cell cell = Coord_Cell(building->Center_Coord());
                value = Map.Unknown_0054E3A0(cell, member->House);
                break;
            }
            case 2: {
                CoordStruct here = member->Coord;
                CoordStruct there = building->Coord;
                value = 0x7FFFFFFF - Coord_Distance(there, here);
                break;
            }
            case 3: {
                CoordStruct here = member->Coord;
                CoordStruct there = building->Coord;
                value = Coord_Distance(there, here);
                break;
            }
            }
            if (value > enemy_best_value && is_enemy) {
                enemy_best = building;
                enemy_best_value = value;
            }
            if (value > best_value) {
                best = building;
                best_value = value;
            }
        }
    }
    if (enemy_best != 0 && enemy_best_value > best_value) {
        return enemy_best;
    }
    if (enemy_only) {
        return enemy_best;
    }
    return best;
}
