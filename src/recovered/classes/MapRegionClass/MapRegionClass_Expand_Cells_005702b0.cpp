#include "shared/map_region.hpp"
#include "shared/cell.hpp"
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &position);
// @ref ?Collect_Boundary_Cells_0056ed10@MapRegionClass@@=0056ed10
// @ref ??0?$VectorClass@VCell@@@@=0042d4a0
// @ref ??_7?$DynamicVectorClass@VCell@@@@6B@=0079c5a0
bool MapRegionClass::Expand_Cells_005702b0()
{
    int index;
    DynamicVectorClass<Cell> *border=Collect_Boundary_Cells_0056ed10();
    DynamicVectorClass<Cell> open;
    open.Set_Growth_Step(50000);
    for(index=0;index<border->Count();++index)open.Add((*border)[index]);
    delete border;
    while(open.Count()>0) {
        index=open.Count()-1;
        Cell position=open[index];
        open.Delete(index);
        for(int facing=0;facing<8;++facing) {
            Cell adjacent=CellClass::Adjacent_Cell(position,facing);
            if(Generation_Cell_In_Bounds_0058da10(adjacent)) {
                UnknownMapGenerationCell &data=unknown_map_cells_a70a24[adjacent.Y*unknown_map_cell_side_84e804+adjacent.X];
                if(data.RegionIndex==-1 && data.unknown_4b) {
                    data.RegionIndex=Index;
                    open.Add(adjacent);
                }
            }
        }
    }
    return true;
}
