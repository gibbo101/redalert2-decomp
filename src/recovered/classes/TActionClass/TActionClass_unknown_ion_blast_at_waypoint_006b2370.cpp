// bool TActionClass::unknown_ion_blast_at_waypoint(...) (0x006B2370)
// Starts a new ion blast at waypoint +0x44 (cell centre, ground height); always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/ion_blast.hpp"
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180
// @ref ??0IonBlastClass@@QAE@UCoordStruct@@@Z=00521270

bool TActionClass::unknown_ion_blast_at_waypoint(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Cell waypoint = unknown_id_source_a3d290->Get_Waypoint_Location(unknown_44);
    CoordStruct coord = Cell_Center(waypoint);
    coord.Z = Map.Unknown_0055A280(coord);
    new IonBlastClass(coord);
    return true;
}
