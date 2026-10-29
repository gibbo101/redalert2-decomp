// void SetDefenseTabCommandClass::Execute(int key) const -- 0x0051B0F0
// Switches the sidebar to tab 1 when that column has anything to build,
// then hands the remembered building (0x006F8A60) to the player's house
// (0x004E7070) with the building its slot 94 names.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/command.hpp"
#include "shared/house.hpp"
#include "shared/mouse_class.hpp"
#include "shared/map_view.hpp"
#include "shared/object.hpp"
#include "shared/house.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Unknown_006F8A60@@YAPAVBuildingClass@@XZ=006f8a60
// @ref ?Unknown_00681730@StripClass@SidebarClass@@QAE_NXZ=00681730
// @ref ?Select_Tab@SidebarClass@@QAEXH@Z=0067d990
// @ref ?unknown_func_4e7070@HouseClass@@QAE_NPAVTechnoClass@@PAVBuildingClass@@@Z=004e7070

BuildingClass *Unknown_006F8A60();

void SetDefenseTabCommandClass::Execute(int key) const
{
    if (Map.Column[1].Unknown_00681730()) {
        Map.Select_Tab(1);
        BuildingClass *building = Unknown_006F8A60();
        if (building != 0) {
            unknown_player_a35db4->unknown_func_4e7070(building->Who_Can_Build_Me(false, false), building);
        }
    }
}
