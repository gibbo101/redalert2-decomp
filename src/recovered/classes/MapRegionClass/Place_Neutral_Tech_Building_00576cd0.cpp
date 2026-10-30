#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/building_view.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
extern char const unknown_neutral_name_7e14b8[];
unsigned __fastcall Map_Random_Range_005797a0(unsigned,unsigned);
// @ref ?unknown_neutral_name_7e14b8@@=007e14b8
// @ref ?Map_Random_Range_005797a0@@=005797a0
// @ref ?FUN_0056dac0@seed_0056dac0@@YI_NPAF@Z=0056dac0
namespace seed_0056dac0 {
bool __fastcall FUN_0056dac0(short *position)
{
    unsigned index=(unsigned)(int)position[1]*(unsigned)unknown_map_cell_side_84e804+(unsigned)(int)position[0];
    return unknown_map_cells_a70a24[index].unknown_45[0]==0;
}
}
void MapRegionClass::Place_Neutral_Tech_Building_00576cd0()
{
    HouseClass *neutral=HouseClass::As_Pointer(HouseTypeClass::Find_Index(unknown_neutral_name_7e14b8));
    bool placed=false;
    int tries=0;
    BuildingClass *building=new BuildingClass(Rules->NeutralTechBuildings[Map_Random_Range_005797a0(0,Rules->NeutralTechBuildings.Count()-1)],neutral);
    while(!placed) {
        if(tries>=100)break;
        Cell position=Cells[Map_Random_Range_005797a0(0,Cells.Count()-1)];
        int height=Map[position].unknown_11b;
        Cell const *list=building->Type->unknown_slot36(1);
        bool clear=true;
        while(list->X!=0x7fff || list->Y!=0x7fff) {
            Cell next=position.unknown_42add0(*list);
            CellClass *cell=&Map[next];
            if(cell->OccupierPtr!=0 || !cell->unknown_47b590() || cell->unknown_11b!=height || cell->unknown_ec==3 || !Map.Unknown_0055A740(cell,true) || !seed_0056dac0::FUN_0056dac0((short *)&cell->MapCoords))clear=false;
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
