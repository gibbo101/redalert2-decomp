#include "shared/map_region.hpp"
bool MapRegionClass::Make_Regions_00570810()
{
    bool success=unknown_map_generator_a6fd68.Expand_All_High_Ground_00583740();
    if(unknown_map_cells_a70a24) {
        int remaining=(int)((unsigned)unknown_map_cell_side_84e804*(unsigned)unknown_map_cell_side_84e804);
        for(int index=0;remaining>0;--remaining,++index) {
            unknown_map_cells_a70a24[index].RegionIndex=-1;
            unknown_map_cells_a70a24[index].unknown_3c=-1;
        }
    }
    for(int reverse=(int)((unsigned)unknown_map_regions_a6fd28.Count()-1u);reverse>=0;--reverse)delete unknown_map_regions_a6fd28[reverse];
    unknown_map_region_next_index_a70a28=0;
    int remaining=(int)((unsigned)unknown_map_cell_side_84e804*(unsigned)unknown_map_cell_side_84e804);
    for(int index=0;remaining>0;--remaining,++index) {
        if(unknown_map_cells_a70a24[index].RegionIndex==-1 && (unsigned char)unknown_map_cells_a70a24[index].Position.Not_Equal_0058db50(Cell(0,0))) {
            MapRegionClass *region=Create_Region_From_Cell_0056e100(&Map[unknown_map_cells_a70a24[index].Position]);
            if(region)region->unknown_1a=false;
        }
    }
    if(success) {
        int index;
        for(index=0;index<unknown_map_regions_a6fd28.Count();++index)unknown_map_regions_a6fd28[index]->Collect_Neighbor_Regions_005709c0();
        for(index=0;index<unknown_map_regions_a6fd28.Count();++index)unknown_map_regions_a6fd28[index]->Make_Region_Connections_00571ed0();
        for(index=0;index<unknown_map_regions_a6fd28.Count();++index) {
            delete unknown_map_regions_a6fd28[index]->NeighborRegionIndices;
            unknown_map_regions_a6fd28[index]->NeighborRegionIndices=0;
        }
    }
    return true;
}
