#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &position);
// @ref ?Build_Region_Border_Cell_List_00581ee0@UnknownMapGenerator@@=00581ee0
// @ref ??0?$VectorClass@VCell@@@@=0042d4a0
// @ref ??_7?$DynamicVectorClass@VCell@@@@6B@=0079c5a0
bool UnknownMapGenerator::Grow_Region_00581940(int region,int rings,Rect area,char setHeight,int height)
{
    DynamicVectorClass<Cell> *border=Build_Region_Border_Cell_List_00581ee0(region);
    DynamicVectorClass<Cell> *next;
    for(int ring=0;ring<rings;++ring) {
        next=new DynamicVectorClass<Cell>;
        next->Set_Growth_Step(3*border->Count());
        for(int index=0;index<border->Count();++index) {
            for(int facing=0;facing<8;++facing) {
                Cell const &borderCell=(*border)[index];
                Cell position=CellClass::Adjacent_Cell(borderCell,facing);
                if(Generation_Cell_In_Bounds_0058da10(position) && area.Is_Point_Within(Point2D(position.X,position.Y))) {
                    UnknownMapGenerationCell &data=MapRegionClass::Get_Cell_Data(position);
                    int oldRegion=data.RegionIndex;
                    bool reclaim=setHeight && oldRegion==region-1;
                    CellClass &cell=Map[position];
                    if((oldRegion==0 || reclaim) && (cell.unknown_47b590() || (reclaim && cell.unknown_47b7e0()))) {
                        next->Add(position);
                        data.RegionIndex=region;
                        if(setHeight && cell.unknown_47b590())Map[position].unknown_11b=height;
                    } else if(oldRegion!=region) {
                        delete border;
                        delete next;
                        return false;
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
