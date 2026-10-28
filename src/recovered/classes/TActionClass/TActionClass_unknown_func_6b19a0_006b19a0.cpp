// bool TActionClass::unknown_func_6b19a0(...) (0x006B19A0)
// Creates a voxel animation of the type at index Data at the waypoint +0x44 (ground height, bridge level counted); always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/voxel_anim.hpp"
#include "shared/voxel_anim_type.hpp"
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180
// @ref ??0VoxelAnimClass@@QAE@PAVVoxelAnimTypeClass@@ABUCoordStruct@@PAVHouseClass@@@Z=0070c800

bool TActionClass::unknown_func_6b19a0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Cell waypoint = unknown_id_source_a3d290->Get_Waypoint_Location(unknown_44);
    CoordStruct coord = Cell_Center(waypoint);
    coord.Z = Map.Unknown_0055A280(coord);
    if ((Map[waypoint].unknown_140 & 0x100) || (Map[waypoint].unknown_140 & 0x400)) {
        coord.Z += unknown_geometry_j;
    }
    new VoxelAnimClass(VoxelAnimTypes[Data], coord, 0);
    return true;
}
