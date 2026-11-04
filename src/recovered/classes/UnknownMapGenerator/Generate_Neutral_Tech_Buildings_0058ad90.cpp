#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
extern char const unknown_neutral_name_7e14b8[];
unsigned __fastcall Map_Random_Range_005797a0(unsigned,unsigned);
extern DynamicVectorClass<MapRegionClass *> unknown_map_regions_a6fd28;
// @ref ?unknown_neutral_name_7e14b8@@=007e14b8
// @ref ?Map_Random_Range_005797a0@@=005797a0
// @ref ?unknown_map_regions_a6fd28@@3V?$DynamicVectorClass@PAVMapRegionClass@@@@A=00a6fd28
inline int Region_Size(MapRegionClass const *region)
{
    return region->unknown_20;
}

inline bool Cell_Is_Free(Cell const &position)
{
    return !MapRegionClass::Get_Cell_Data(position).unknown_45[0];
}

inline bool Is_List_End(Cell const *list)
{
    return list->X==0x7fff && list->Y==0x7fff;
}

inline int Cell_Height(Cell const &position)
{
    return Map[position].unknown_11b;
}

void UnknownMapGenerator::Generate_Neutral_Tech_Buildings_0058ad90()
{
    if(SeedOptions.MapType==2) {
        int count=Map_Random_Range_005797a0(0,2);
        for(int pass=count;pass>0;pass--) {
            for(int index=0;index<unknown_map_regions_a6fd28.Count();index++) {
                if(Region_Size(unknown_map_regions_a6fd28[index])>0) {
                    unknown_map_regions_a6fd28[index]->Place_Neutral_Tech_Building_00576cd0();
                }
            }
        }
    } else {
        HouseClass *neutral=HouseClass::As_Pointer(HouseTypeClass::Find_Index(unknown_neutral_name_7e14b8));
        int count=Map_Random_Range_005797a0(0,4);
        for(int pass=count;pass>0;pass--) {
            bool placed=false;
            int tries=0;
            BuildingClass *building=new BuildingClass(Rules->NeutralTechBuildings[Map_Random_Range_005797a0(0,Rules->NeutralTechBuildings.Count()-1)],neutral);
            while(!placed) {
                if(tries>=100)break;
                Cell position=Pick_Random_Clear_Map_Cell();
                int height=Cell_Height(position);
                Cell const *list=building->Type->unknown_slot36(1);
                bool clear=true;
                while(!Is_List_End(list)) {
                    Cell next=position + *list;
                    CellClass *cell=&Map[next];
                    if(cell->OccupierPtr!=0 || !cell->unknown_47b590() || cell->unknown_11b!=height || cell->unknown_ec==3 || !Map.Unknown_0055A740(cell,true) || !Cell_Is_Free(cell->MapCoords))clear=false;
                    ++list;
                    if(!clear)break;
                }
                if(clear) {
                    if(building->unknown_slot53(&CoordStruct(position.X*256+128,position.Y*256+128,0),0))placed=true;
                }
                ++tries;
            }
            if(!placed)delete building;
        }
    }
}
