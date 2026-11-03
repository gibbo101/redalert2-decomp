// void DisplayClass::Active_Click_0049E870(ObjectClass *object, Cell cell, int action) (0x0049E870)
// TibSun DisplayClass::Active_Click: passes a click on to every selected object. The cell is clipped to the
// map; a waypoint in it sets every selected object's waypoint path and id (ObjectClass slot 99) and clears
// TechnoClass +0x37F for the foot objects. With an object, each selected object acts on it (slot 28 then
// slot 78); without one, actions 1 and 0x33 and action 2 pass the cell twice and every other action passes
// the cell and Cell(-1, -1) (slot 27 then slot 77). The voice flag 0x007D88D6 is cleared after each order
// and set again at the end. RA2 drops TibSun's group-move spreading.
#include "shared/display.hpp"
#include "shared/house_screen.hpp"
#include "shared/object.hpp"
#include "shared/techno.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_a40d13@@3_NA=00a40d13
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60
// @ref ?unknown_sound_enabled_7d88d6@@3_NA=007d88d6

// TibSun ObjectClass::Is_Foot: a byte result even for a null object.
static inline bool Is_Foot(ObjectClass const *object)
{
    bool foot = false;
    if (object) foot = object->AbstractFlags.IsFoot;
    return foot;
}

void DisplayClass::Active_Click_0049E870(ObjectClass *object, Cell cell, int action)
{
    int index;
    int waypoint_path = -1;
    char waypoint_id = 0;

    if (unknown_a40d13) {
        return;
    }

    cell = Map.Clip_To_Map(cell);
    WaypointClass *waypoint = unknown_player_a35db4->unknown_func_4ed200(cell);
    if (waypoint != 0) {
        unknown_player_a35db4->unknown_func_4ed2b0(waypoint, &waypoint_path, &waypoint_id);
    }

    for (index = 0; index < unknown_objects_a40c60.Count(); index++) {
        unknown_objects_a40c60[index]->unknown_slot99(waypoint_path, waypoint_id);
        if (Is_Foot(unknown_objects_a40c60[index])) {
            TechnoClass *techno = (TechnoClass *)unknown_objects_a40c60[index];
            techno->unknown_37f = false;
        }
    }

    if (object != 0) {
        for (index = 0; index < unknown_objects_a40c60.Count(); index++) {
            unknown_objects_a40c60[index]->unknown_slot78(unknown_objects_a40c60[index]->unknown_slot28(object, false), (int)object, false);
            unknown_sound_enabled_7d88d6 = false;
        }
    } else if (action == 1 || action == 0x33) {
        for (index = 0; index < unknown_objects_a40c60.Count(); index++) {
            unknown_objects_a40c60[index]->unknown_slot77(unknown_objects_a40c60[index]->unknown_slot27(&cell, false, false), (int)&cell, (int)&cell, false);
            unknown_sound_enabled_7d88d6 = false;
        }
    } else if (action == 2) {
        int count = unknown_objects_a40c60.Count();
        for (index = 0; index < count; index++) {
            unknown_objects_a40c60[index]->unknown_slot77(unknown_objects_a40c60[index]->unknown_slot27(&cell, false, false), (int)&cell, (int)&cell, false);
            unknown_sound_enabled_7d88d6 = false;
        }
    } else {
        for (index = 0; index < unknown_objects_a40c60.Count(); index++) {
            Cell none(-1, -1);
            unknown_objects_a40c60[index]->unknown_slot77(unknown_objects_a40c60[index]->unknown_slot27(&cell, false, false), (int)&cell, (int)&none, false);
            unknown_sound_enabled_7d88d6 = false;
        }
    }
    unknown_sound_enabled_7d88d6 = true;
}
