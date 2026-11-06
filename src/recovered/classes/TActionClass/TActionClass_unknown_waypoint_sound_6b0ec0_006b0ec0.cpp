// bool TActionClass::unknown_waypoint_sound_6b0ec0(...) (0x006B0EC0)
// Plays sound Data.Value on the object at waypoint +0x44, else starts a static sound there; always true.
#include "shared/taction.hpp"
#include "shared/object.hpp"
#include "shared/id_source.hpp"
#include "shared/sound_play.hpp"
#include "shared/voc_static.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Waypoint_Coord@UnknownIDSource@@QBE?AUCoordStruct@@H@Z=006631c0
// @ref ?unknown_4717b0@CellClass@@QBEPAVObjectClass@@XZ=004717b0
// @ref ?Cell_Terrain@CellClass@@QBEPAVObjectClass@@_N@Z=004717e0
// @ref ?unknown_cell_abfdb0@@3VCell@@A=00abfdb0

bool TActionClass::unknown_waypoint_sound_6b0ec0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    CoordStruct coord = unknown_id_source_a3d290->Waypoint_Coord(unknown_44);
    ObjectClass *target = Building_Or_Terrain_At_006B0E40(coord);
    if (target != 0) {
        target->unknown_func_5d5520(Data.Value);
    } else {
        Voc_Static_Add(Data.Value, coord, 1);
    }
    return true;
}


