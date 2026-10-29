// void CenterBaseCommandClass::Execute(int key) const -- 0x0051C140
// Centres the view on the player's construction yard (the first one with
// +0x32B set, else the last found), else on another building, else on a
// base unit of the player's side (Rules BaseUnit).
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/command.hpp"
#include "shared/house.hpp"
#include "shared/mouse_class.hpp"
#include "shared/map_view.hpp"
#include "shared/object.hpp"
#include "shared/building_type_class.hpp"
#include "shared/rules.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Unknown_006A66B0@Tactical@@QAEXABUCoordStruct@@@Z=006a66b0
// @ref ?Unknown_004994D0@DisplayClass@@QAE?AVCell@@ABV2@@Z=004994d0
// @ref ?Unknown_0049EC60@DisplayClass@@QAEXPAVObjectClass@@@Z=0049ec60

void CenterBaseCommandClass::Execute(int key) const
{
    CoordStruct yard = unknown_geometry_l;
    CoordStruct other = unknown_geometry_l;
    if (unknown_player_a35db4->CurBuildings) {
        for (int index = 0; index < unknown_BuildingClass_list_00a40af8.Count(); index++) {
            BuildingClass *building = unknown_BuildingClass_list_00a40af8[index];
            if (building != 0 && !building->unknown_76 && building->House->Unknown_004F52B0()) {
                if (building->Type->ConstructionYard) {
                    yard = building->Center_Coord();
                    if (building->unknown_32b) {
                        break;
                    }
                } else if (other == unknown_geometry_l) {
                    other = building->Center_Coord();
                }
            }
        }
    }
    if (other == unknown_geometry_l && yard == unknown_geometry_l && unknown_player_a35db4->unknown_228) {
        for (int index = 0; index < Units.Count(); index++) {
            UnitClass *unit = Units[index];
            if (unit != 0 && !unit->unknown_76 && unit->House->Unknown_004F52B0()
                && unit->Type == unknown_player_a35db4->Unknown_004EF6F0(Rules->BaseUnit)) {
                yard = unit->Center_Coord();
                break;
            }
        }
    }
    if (yard != unknown_geometry_l) {
        unknown_tactical_83996c->Unknown_006A66B0(yard);
    } else if (other != unknown_geometry_l) {
        unknown_tactical_83996c->Unknown_006A66B0(other);
    }
    if (Map.unknown_11a4 != 0) {
        Map.Unknown_004994D0(unknown_geometry_k);
    }
    Map.Unknown_0049EC60(0);
    Map.Flag_To_Redraw(true);
}
