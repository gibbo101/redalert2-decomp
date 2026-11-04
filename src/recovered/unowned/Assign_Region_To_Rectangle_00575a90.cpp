#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
extern DynamicVectorClass<MapRegionClass *> unknown_map_regions_a6fd28;
// @ref ?unknown_map_regions_a6fd28@@=00a6fd28
// @ref ?unknown_map_cells_a70a24@@=00a70a24
// @ref ?unknown_map_cell_side_84e804@@=0084e804
// @ref ?unknown_map_min_a70a1c@@=00a70a1c
// @ref ?unknown_map_max_a70a20@@=00a70a20
// @ref ?Find_Map_Region_By_Index_00575ce0@@=00575ce0
// @ref ?Generation_Cell_In_Bounds_0058da10@@=0058da10
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &cell);
MapRegionClass *__fastcall Find_Map_Region_By_Index_00575ce0(int index);
void __stdcall Assign_Region_To_Rectangle_00575a90(Rect const &area,int index)
{
    for(int y=area.Y;y<area.Y+area.Height;y++) {
        for(int x=area.X;x<area.X+area.Width;x++) {
            Cell const position((short)x,(short)y);
            if(Generation_Cell_In_Bounds_0058da10(position)) {
                Set_Cell_Region_Index_0056e970(position,index);
                CellClass &target=Map[position];
                target.unknown_11b=(char)Find_Map_Region_By_Index_00575ce0(index)->unknown_10;
            }
        }
    }
}

#include "shared/coord.hpp"
extern int unknown_map_min_a70a1c,unknown_map_max_a70a20;
// @ref ?unknown_map_min_a70a1c@@3HA=00a70a1c
// @ref ?unknown_map_max_a70a20@@3HA=00a70a20
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &cell)
{
    int x=cell.X;
    int y=cell.Y;
    bool inside=(x+y>unknown_map_min_a70a1c && x-y<unknown_map_min_a70a1c &&
           y-x<unknown_map_min_a70a1c && x+y<=unknown_map_max_a70a20) ? true : false;
    return inside;
}

#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/map_region.hpp"
extern DynamicVectorClass<MapRegionClass *> unknown_map_regions_a6fd28;
// @ref ?unknown_map_regions_a6fd28@@3V?$DynamicVectorClass@PAVMapRegionClass@@@@A=00a6fd28
MapRegionClass *__fastcall Find_Map_Region_By_Index_00575ce0(int index)
{
    for(int i=0;i<unknown_map_regions_a6fd28.Count();i++)
        if(unknown_map_regions_a6fd28[i]->Index==index)
            return unknown_map_regions_a6fd28[i];
    return 0;
}
