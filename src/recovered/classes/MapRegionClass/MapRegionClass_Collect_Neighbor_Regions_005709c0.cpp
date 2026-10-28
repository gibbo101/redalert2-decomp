// @ref ??_7?$DynamicVectorClass@H@@6B@=0079da94
// @ref ??_E?$DynamicVectorClass@H@@UAEPAXI@Z=0046cf50
// @ref ??_G?$DynamicVectorClass@H@@UAEPAXI@Z=0046cf50
// @ref ??8?$VectorClass@H@@UBE_NABV0@@Z=0046d070
// @ref ?Resize@?$DynamicVectorClass@H@@UAE_NHPBH@Z=0046d250
// @ref ?Clear@?$DynamicVectorClass@H@@UAEXXZ=0046cc80
// @ref ?ID@?$DynamicVectorClass@H@@UAEHABH@Z=0046d350
// @ref ?ID@?$DynamicVectorClass@H@@UAEHPBH@Z=0046ccb0
// @ref ?Fetch@?$VectorClass@H@@UBEHH@Z=0046ccd0
// @ref ??_7?$VectorClass@H@@6B@=0079d9d4
// @ref ??_E?$VectorClass@H@@UAEPAXI@Z=0046da70
// @ref ??_G?$VectorClass@H@@UAEPAXI@Z=0046da70
// @ref ?Resize@?$VectorClass@H@@UAE_NHPBH@Z=0046d0b0
// @ref ?Clear@?$VectorClass@H@@UAEXXZ=0046d160
// @ref ?ID@?$VectorClass@H@@UAEHABH@Z=0046d190
// @ref ?ID@?$VectorClass@H@@UAEHPBH@Z=0046d1d0
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/map_region.hpp"
// @ref ?unknown_map_region_next_index_a70a28@@3HA=00a70a28
// @ref ?unknown_map_cell_side_84e804@@3HA=0084e804
// @ref ?unknown_map_cells_a70a24@@3PAUUnknownMapGenerationCell@@A=00a70a24
// @ref ?unknown_map_min_a70a1c@@3HA=00a70a1c
// @ref ?unknown_map_max_a70a20@@3HA=00a70a20
// @ref ?unknown_adjacent_851a70@@3QBVCell@@B=00851a70
// @ref ?Collect_Boundary_Cells_0056ed10@MapRegionClass@@=0056ed10
// @ref ??0?$VectorClass@H@@=0046d020
void MapRegionClass::Collect_Neighbor_Regions_005709c0()
{
    NeighborRegionIndices=new DynamicVectorClass<int>;
    unsigned char *seen=new unsigned char[unknown_map_region_next_index_a70a28];
    int index;
    for(index=0;index<unknown_map_region_next_index_a70a28;index++)
        seen[index]=0;
    DynamicVectorClass<Cell> *boundary=Collect_Boundary_Cells_0056ed10();
    for(index=0;index<boundary->Count();index++) {
        Cell cell=(*boundary)[index];
        for(int direction=0;direction<8;direction++) {
            Cell next=cell+unknown_adjacent_851a70[direction&7];
            if(next.Y+next.X>unknown_map_min_a70a1c && next.X-next.Y<unknown_map_min_a70a1c &&
               next.Y-next.X<unknown_map_min_a70a1c && next.Y+next.X<=unknown_map_max_a70a20) {
                if(unknown_map_cells_a70a24) {
                    int regionIndex=unknown_map_cells_a70a24[next.Y*unknown_map_cell_side_84e804+next.X].RegionIndex;
                    if(regionIndex>=0) seen[regionIndex]=1;
                }
            }
        }
    }
    for(index=0;index<unknown_map_region_next_index_a70a28;index++)
        if(seen[index] && index!=Index) NeighborRegionIndices->Add(index);
    CellCount=0;
    int totalCells=unknown_map_cell_side_84e804*unknown_map_cell_side_84e804;
    for(index=0;index<totalCells;index++) {
        if(unknown_map_cells_a70a24[index].RegionIndex==Index &&
           unknown_map_cells_a70a24[index].Position!=Cell(0,0)) CellCount++;
    }
    delete boundary;
    delete[] seen;
}
