// bool TActionClass::unknown_particle_system_at_waypoint(...) (0x006AFA00)
// Creates the particle system of the type at index Data over the cell centre of waypoint +0x44 (ground height); always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/particle_system.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180
// @ref _unknown_geometry_l=00abfdd0

bool TActionClass::unknown_particle_system_at_waypoint(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Cell waypoint = unknown_id_source_a3d290->Get_Waypoint_Location(unknown_44);
    CoordStruct coord = Cell_Center(waypoint);
    coord.Z = Map.Unknown_0055A280(Cell_Center(waypoint));
    new ParticleSystemClass(ParticleSystemTypes[Data], coord, 0, 0, unknown_geometry_l);
    return true;
}
