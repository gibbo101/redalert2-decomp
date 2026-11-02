// void MapRegionClass::Destroy_Cell_Regions() (0x0056E790): clears every generation cell's region links
// (RegionIndex, +0x3C = -1) and deletes the regions newest first (each ~MapRegionClass removes itself from
// unknown_map_regions_a6fd28), then resets the next region index. Defined here out of line; the generator's
// destructor 0x005771B0 and Init_Regions in Generate_Random_Map 0x0057A0D0 expand it inline.
#include "shared/map_region.hpp"
extern DynamicVectorClass<MapRegionClass *> unknown_map_regions_a6fd28;
void MapRegionClass::Destroy_Cell_Regions()
{
    int index;
    if(unknown_map_cells_a70a24) {
        int size=(int)((unsigned)unknown_map_cell_side_84e804*(unsigned)unknown_map_cell_side_84e804);
        for(index=0;index<size;++index) {
            unknown_map_cells_a70a24[index].RegionIndex=-1;
            unknown_map_cells_a70a24[index].unknown_3c=-1;
        }
    }
    for(index=(int)((unsigned)unknown_map_regions_a6fd28.Count()-1u);index>=0;--index) {
        MapRegionClass *region=unknown_map_regions_a6fd28[index];
        if(region)delete region;
    }
    unknown_map_region_next_index_a70a28=0;
 }
