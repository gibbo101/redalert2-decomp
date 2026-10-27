#include "shared/building.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?Current@FacingClass@@=004b8be0
// @ref ?unknown_4717b0@CellClass@@=004717b0
// Find a same-owner fence post along the requested cell direction.
BuildingClass *BuildingClass::unknown_44ddb0(int facing, bool through_fences, int max_range)
{
    int range=1;
    if(max_range<0) {
        if(Type->LaserFencePost) {
            range=Type->GuardRange.Value>>8;
            if(range<=1) range=1;
        }
    } else range=max_range;
    int direction=facing&3;
    Cell cell=Coord_Cell(Center_Coord());
    BuildingClass *result=0;
    for(int index=0;index<range;++index) {
        Cell const &offset=AdjacentCell[facing&7];
        Cell next=Cell((short)(offset.X+cell.X),(short)(offset.Y+cell.Y));
        cell=next;
        BuildingClass *building=static_cast<BuildingClass *>(Map[cell].unknown_4717b0());
        if(building) {
            if(building->Type->LaserFencePost && Owner()==building->Owner()) result=building;
            if(!through_fences || !building->Type->LaserFence || Owner()!=building->Owner()
               || (Dir_To_8(building->unknown_2e0.Current())&3)!=direction) break;
        }
    }
    return result;
}
