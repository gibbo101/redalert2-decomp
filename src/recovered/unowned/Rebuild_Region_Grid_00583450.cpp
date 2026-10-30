// @ref ?Expand_Cells_005702b0@MapRegionClass@@=005702b0
// Actual ECX is read at+3C: MapSeed prefix/reference/constness and free ownership are hypotheses.
#include "shared/map_region.hpp"
#include "shared/map_seed.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
extern DynamicVectorClass<MapRegionClass *> unknown_map_regions_a6fd28;
// Existing exact global/type/name; no definition or initializer.
// @ref ?unknown_map_regions_a6fd28@@3V?$DynamicVectorClass@PAVMapRegionClass@@@@A=00a6fd28
// @ref ??1MapRegionClass@@QAE@XZ=0056d970
// @ref ?Grow_Border_00570040@MapRegionClass@@=00570040
// @ref ?Build_Map_Region_0056e100@@=0056e100
// Physical ECX CellClass pointer, no stack argument, full EAX constructed region or explicit-zero path.
// Free/member spelling and name are hypotheses; no outside-range body is promoted.
MapRegionClass *__fastcall Build_Map_Region_0056e100(CellClass *cell);
void __fastcall Rebuild_Region_Grid_00583450(MapSeedClass const &options)
{
    if(unknown_map_cells_a70a24!=0) {
        int remaining=(int)((unsigned int)unknown_map_cell_side_84e804*(unsigned int)unknown_map_cell_side_84e804);
        for(int index=0;remaining>0;--remaining,++index) {
            MapRegionClass::Get_Cell_Data(index).RegionIndex=-1;
            MapRegionClass::Get_Cell_Data(index).unknown_3c=-1;
        }
    }
    for(int reverse=(int)((unsigned int)unknown_map_regions_a6fd28.Count()-1u);reverse>=0;--reverse) {
        MapRegionClass *region=unknown_map_regions_a6fd28[reverse];
        delete region;
    }
    {
        int remaining=(int)((unsigned int)unknown_map_cell_side_84e804*(unsigned int)unknown_map_cell_side_84e804);
        unknown_map_region_next_index_a70a28=0;
        for(int index=0;remaining>0;--remaining,++index) {
            Cell position=MapRegionClass::Get_Cell_Data(index).Position;
            CellClass &cell=Map[position];
            if(MapRegionClass::Get_Cell_Data(index).RegionIndex==-1 &&
               (MapRegionClass::Get_Cell_Data(index).Position.X!=0 || MapRegionClass::Get_Cell_Data(index).Position.Y!=0) &&
               (cell.unknown_47b7e0() || cell.unknown_47b9c0())) {
                Build_Map_Region_0056e100(&cell);
            }
        }
    }
    for(int index=0;index<unknown_map_regions_a6fd28.Count();++index) {
        MapRegionClass *region=unknown_map_regions_a6fd28[index];
        if(region->unknown_14!=0) {
            int special;
            if(options.MapType==3 || options.MapType==4)special=1;
            else special=0;
            region->Grow_Border_00570040(4+(region->CellCount>8000)+!(unsigned char)special);
            region->Expand_Cells_005702b0();
        }
    }
    {
        int remaining=(int)((unsigned int)unknown_map_cell_side_84e804*(unsigned int)unknown_map_cell_side_84e804);
        for(int index=0;remaining>0;--remaining,++index) {
            if(MapRegionClass::Get_Cell_Data(index).RegionIndex==-1 &&
               (MapRegionClass::Get_Cell_Data(index).Position.X!=0 || MapRegionClass::Get_Cell_Data(index).Position.Y!=0)) {
                MapRegionClass *region=Build_Map_Region_0056e100(&Map[MapRegionClass::Get_Cell_Data(index).Position]);
                if(region!=0)region->unknown_1a=false;
            }
        }
    }
}
