#include "shared/voxel_anim.hpp"
#include "shared/house.hpp"
#include "shared/map_cell_view.hpp"

bool VoxelAnimClass::unknown_slot63(Rect *bounds, bool arg2, bool arg3)
{
    CellClass *cell = &Map[Center_Coord()];
    if (cell->unknown_12c & 0x10) {
        unknown_75 = true;
    }
    return ObjectClass::unknown_slot63(bounds, arg2, false);
}
