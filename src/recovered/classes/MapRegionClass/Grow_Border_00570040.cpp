#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &position);
// @ref ?Collect_Boundary_Cells_0056ed10@MapRegionClass@@=0056ed10
// @ref ??0?$VectorClass@VCell@@@@=0042d4a0
// @ref ??_7?$DynamicVectorClass@VCell@@@@6B@=0079c5a0
bool MapRegionClass::Grow_Border_00570040(int steps)
{
    DynamicVectorClass<Cell> *border=Collect_Boundary_Cells_0056ed10();
    for(int step=0;step<steps;++step) {
        DynamicVectorClass<Cell> *next=new DynamicVectorClass<Cell>;
        next->Set_Growth_Step(3*border->Count());
        for(int index=0;index<border->Count();++index) {
            for(int facing=0;facing<8;++facing) {
                Cell position=CellClass::Adjacent_Cell((*border)[index],facing);
                if(Generation_Cell_In_Bounds_0058da10(position)) {
                    if(Map[position].unknown_11b==unknown_10) {
                        UnknownMapGenerationCell &data=MapRegionClass::Get_Cell_Data(position);
                        int region=data.RegionIndex;
                        if(region==-1 && (Map[position].unknown_47b590() || Map[position].unknown_47b9c0())) {
                            next->Add(position);
                            data.RegionIndex=Index;
                            Map[position].unknown_11b=(char)unknown_10;
                        } else if(region!=Index) {
                            delete border;
                            delete next;
                            return false;
                        }
                    }
                }
            }
        }
        delete border;
        border=next;
    }
    delete border;
    return true;
}
