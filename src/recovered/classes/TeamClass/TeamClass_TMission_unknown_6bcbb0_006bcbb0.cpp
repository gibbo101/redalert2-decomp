// void TeamClass::TMission_unknown_6bcbb0(ScriptMissionClass const &mission, bool unknown) (0x006BCBB0)
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/house.hpp"
#include "shared/techno_type.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/id_source.hpp"
// @ref ?unknown_4eec70@HouseClass@@QAEXPAV1@@Z=004eec70

// Complete original-backed BuildingClass-vector copies; no helper source credit.
// @ref ??_7?$VectorClass@PAVBuildingClass@@@@6B@=007a2384
// @ref ??_7?$DynamicVectorClass@PAVBuildingClass@@@@6B@=007a2364
// @ref ??_G?$VectorClass@PAVBuildingClass@@@@UAEPAXI@Z=004dbc90
// @ref ??_E?$VectorClass@PAVBuildingClass@@@@UAEPAXI@Z=004dbc90
// @ref ??_G?$DynamicVectorClass@PAVBuildingClass@@@@UAEPAXI@Z=004dbce0
// @ref ??_E?$DynamicVectorClass@PAVBuildingClass@@@@UAEPAXI@Z=004dbce0
// @ref ??0?$VectorClass@PAVBuildingClass@@@@QAE@IPBQAVBuildingClass@@@Z=004f8a90

void TeamClass::TMission_unknown_6bcbb0(ScriptMissionClass const &mission, bool unknown)
{
    bool found = true;
    if (unknown_30 == 0) {
        int count = 0;
        int index;
        for (index = 0; index < Owner->ScoutNodes.Count(); index++) {
            if (!Owner->ScoutNodes[index].IsPreferred) {
                count++;
            }
        }
        if (count > 0) {
            int pick = unknown_id_source_a3d290->Random()(0, count - 1);
            for (index = 0; index < Owner->ScoutNodes.Count(); index++) {
                if (!Owner->ScoutNodes[index].IsPreferred) {
                    if (pick == 0) {
                        unknown_30 = (AbstractClass *)Owner->ScoutNodes[index].House;
                        break;
                    }
                    pick--;
                }
            }
            DynamicVectorClass<BuildingClass *> list;
            for (index = 0; index < unknown_BuildingClass_list_00a40af8.Count(); index++) {
                if ((HouseClass *)unknown_30 == unknown_BuildingClass_list_00a40af8[index]->House) {
                    list.Add(unknown_BuildingClass_list_00a40af8[index]);
                }
            }
            if (list.Count() > 0) {
                BuildingClass *building = list[unknown_id_source_a3d290->Random()(0, list.Count() - 1)];
                FootClass *leader = unknown_func_6baa60();
                Point2D radius(1, 1);
                Cell no_cell(0, 0);
                CoordStruct coord = building->Coord;
                Cell dest = Map.Unknown_005502E0(Coord_Cell(coord), leader->unknown_slot32()->SpeedType, -1, 0, false,
                    radius, 0, 0, 0, 1, no_cell, 0);
                if (dest != unknown_geometry_k) {
                    unknown_func_6b79e0(&Map[dest]);
                } else {
                    unknown_func_6b79e0(0);
                }
            } else {
                Owner->unknown_4eec70((HouseClass *)unknown_30);
                unknown_30 = 0;
            }
        } else {
            found = false;
        }
    } else {
        FootClass *leader = unknown_func_6baa60();
        if (leader != 0 && leader->Mission != 2 && leader->MissionQueue != 2) {
            Owner->unknown_4eec70((HouseClass *)unknown_30);
            unknown_30 = 0;
        }
    }
    unknown_func_6ba1a0();
    if (found) {
        StepCompleted = false;
    } else {
        StepCompleted = true;
    }
}
