// PRIVATE Building family free cell traversal; callee signature is a hypothesis.
#include "shared/building.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
extern Cell const AdjacentCell[8];
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?unknown_44e260@BuildingClass@@QAEXH_N@Z=0044e260
inline int Building_Direction_To_4_0044e440(UnknownFacingDir const &direction)
{
    return (((*(unsigned int const *)&direction >> 12)+1)>>1)&3;
}
inline Cell Building_Adjacent_Fence_Cell_0044e440(Cell const &cell,int facing)
{
    Cell const &offset=AdjacentCell[facing&7];
    return Cell(offset.X+cell.X,offset.Y+cell.Y);
}
void __fastcall Building_Refresh_Fence_Cell_0044e440(Cell const &origin)
{
    CellClass *cell=&Map[origin];
    if(!cell)return;
    BuildingClass *fence=static_cast<BuildingClass *>(cell->unknown_4717b0());
    if(!fence || !fence->Type->LaserFence)return;
    int facing=Building_Direction_To_4_0044e440(fence->unknown_2e0.Current());
    BuildingClass *found=0;
    Cell previous=origin;
    Cell next=Building_Adjacent_Fence_Cell_0044e440(previous,facing);
    Cell const &probe=next;
    while(probe!=previous) {
        found=static_cast<BuildingClass *>(Map[probe].unknown_4717b0());
        if(!found)goto destroy;
        if(found->Type->LaserFencePost) {
            found->unknown_44e260(facing|4,false);
            break;
        }
        if(!found->Type->LaserFence)goto destroy;
        previous=probe;
        next=Building_Adjacent_Fence_Cell_0044e440(probe,facing);
    }
    if(found)return;
destroy:
    fence->unknown_slot60();
}
