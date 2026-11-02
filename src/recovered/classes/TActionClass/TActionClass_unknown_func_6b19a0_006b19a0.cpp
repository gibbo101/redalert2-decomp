// bool TActionClass::unknown_func_6b19a0(...) (0x006B19A0)
// Creates a voxel animation of the type at index Data.Value at the waypoint +0x44 (ground height, bridge level counted); always true.
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
    CoordStruct coord = CoordStruct(waypoint);
    coord.Z = Map.Unknown_0055A280(coord);
    unsigned int bridge_flags = Map[waypoint].unknown_140;
    if ((bridge_flags & 0x100) || (Map[waypoint].unknown_140 & 0x400)) {
        int bridge_height = unknown_geometry_j;
        coord.Z += bridge_height;
    }
    new VoxelAnimClass(VoxelAnimTypes[Data.Value], coord, 0);
    return true;
}


