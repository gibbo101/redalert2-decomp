// bool TActionClass::unknown_sound_at_random_waypoint(...) (0x006B0D90)
// Plays the static sound Data.Value at a random one of the set waypoints 0..100 (the cell list stops at sizeof(list) entries, as the original); always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/sound_play.hpp"
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180

bool TActionClass::unknown_sound_at_random_waypoint(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Cell cells[100];
    int count = 0;
    for (int waypoint = 0; waypoint < 101; waypoint++) {
        if (unknown_id_source_a3d290->Unknown_00663240(waypoint)) {
            cells[count++] = unknown_id_source_a3d290->Get_Waypoint_Location(waypoint);
            if (count == sizeof(cells)) {
                break;
            }
        }
    }
    Voc_Static_Add(Data.Value, CoordStruct(cells[Random_Pick(0, count - 1)]), 0);
    return true;
}


