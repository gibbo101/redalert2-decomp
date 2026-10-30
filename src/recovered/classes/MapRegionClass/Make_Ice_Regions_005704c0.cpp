#include "shared/map_region.hpp"
#include "shared/unknown_map_generator.hpp"
extern DynamicVectorClass<MapRegionClass *> unknown_map_regions_a6fd28;
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &position);
// @ref ?unknown_map_regions_a6fd28@@3V?$DynamicVectorClass@PAVMapRegionClass@@@@A=00a6fd28
// @ref ?Generation_Cell_In_Bounds_0058da10@@=0058da10
// @ref ?Split_Region_0056ef20@MapRegionClass@@=0056ef20
// @ref ??1MapRegionClass@@QAE@XZ=0056d970
// Existing real destructor body, needed by the original inline delete site.
MapRegionClass::~MapRegionClass()
{
    if(unknown_00!=0) {
        delete static_cast<DynamicVectorClass<Cell> *>(unknown_00);
        unknown_00=0;
    }
    unknown_map_regions_a6fd28.Delete(this);
}
void MapRegionClass::Make_Ice_Regions_005704c0()
{
    int index;
    for(index=0;index<unknown_map_regions_a6fd28.Count();++index) {
        unknown_map_regions_a6fd28[index]->Cells.Clear();
        unknown_map_regions_a6fd28[index]->CellCount=0;
        unknown_map_regions_a6fd28[index]->Bounds=Rect(9999,9999,0,0);
    }
    int size=unknown_map_cell_side_84e804*unknown_map_cell_side_84e804;
    for(index=size-1;index>=0;--index) {
        UnknownMapGenerationCell &data=MapRegionClass::Get_Cell_Data(index);
        Cell position=data.Position;
        int y=position.Y;
        int x=position.X;
        if(Generation_Cell_In_Bounds_0058da10(position)) {
            int id=data.RegionIndex;
            if(id>=0 && id<unknown_map_regions_a6fd28.Count()) {
                ++unknown_map_regions_a6fd28[id]->CellCount;
                unknown_map_regions_a6fd28[id]->Cells.Add(position);
                Rect &rect=unknown_map_regions_a6fd28[id]->Bounds;
                if(!rect.Width) {
                    rect.X=x;
                    rect.Y=y;
                    rect.Width=1;
                    rect.Height=1;
                }
                int oldX=rect.X;
                if(x>=rect.X+rect.Width)rect.Width=x-oldX+1;
                if(x<oldX) {
                    int oldWidth=rect.Width;
                    rect.X=x;
                    rect.Width=oldX-x+oldWidth;
                }
                int oldY=rect.Y;
                if(y>=rect.Y+rect.Height)rect.Height=y-oldY+1;
                if(y<oldY) {
                    int oldHeight=rect.Height;
                    rect.Y=y;
                    rect.Height=oldY-y+oldHeight;
                }
            }
        }
    }
    double sizeLimit=(unknown_map_generator_a6fd68.SeedOptions.RegionSize*0.005+0.05)*unknown_map_generator_a6fd68.unknown_180*unknown_map_generator_a6fd68.unknown_184;
    int limit=(int)(sizeLimit+sizeLimit);
    while(true) {
        bool restart=false;
        for(index=0;index<unknown_map_regions_a6fd28.Count();++index) {
            MapRegionClass *region=unknown_map_regions_a6fd28[index];
            if(!region->unknown_1a && !region->unknown_14) {
                if(region->CellCount>limit) {
                    if(region->Split_Region_0056ef20()) {
                        delete region;
                        restart=true;
                        break;
                    }
                } else region->unknown_1a=true;
            }
        }
        if(!restart)break;
    }
}
