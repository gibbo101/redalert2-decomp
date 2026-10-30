#include "shared/unknown_map_generator.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/building_view.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/building_type_list.hpp"
extern char *unknown_urban_building_names_7e0be8[18];
extern char const unknown_neutral_name_7e14b8[];
unsigned __fastcall Map_Random_Range_005797a0(unsigned,unsigned);
// @ref ?unknown_urban_building_names_7e0be8@@=007e0be8
// @ref ?unknown_neutral_name_7e14b8@@=007e14b8
// @ref ?Map_Random_Range_005797a0@@=005797a0
void UnknownMapGenerator::Generate_Urban_Buildings_00587cf0(DynamicVectorClass<Cell> &cells)
{
    int count=Map_Random_Range_005797a0(cells.Count()/20,cells.Count()/10)/2;
    int tries=0;
    int placed=0;
    DynamicVectorClass<char *> names;
    for(int index=0;index<18;++index)names.Add(unknown_urban_building_names_7e0be8[index]);
    HouseClass *neutral=HouseClass::As_Pointer(HouseTypeClass::Find_Index(unknown_neutral_name_7e14b8));
    if(count>0) {
        while(true) {
            if(tries>=2*count || names.Count()<=1)break;
            int nameIndex=Map_Random_Range_005797a0(0,names.Count()-1);
            int typeIndex=BuildingTypeClass::From_Name(names[nameIndex]);
            {
                BuildingClass *building=new BuildingClass(BuildingTypes[typeIndex],neutral);
                int attempts=0;
                bool wasPlaced=false;
                while(!wasPlaced) {
                    if(attempts>=60)break;
                    Cell position=cells[Map_Random_Range_005797a0(0,cells.Count()-1)];
                    Cell const *list=building->Type->unknown_slot36(1);
                    bool clear=true;
                    while(list->X!=0x7fff || list->Y!=0x7fff) {
                        Cell next=position.unknown_42add0(*list);
                        CellClass *cell=&Map[next];
                        if((!cell->unknown_47b880() && !cell->unknown_47b860()) || cell->OccupierPtr!=0 || cell->unknown_ec==3 || !Map.Unknown_0055A740(cell,true))clear=false;
                        ++list;
                        if(!clear)break;
                    }
                    if(clear) {
                        CoordStruct point(position.X*256+128,position.Y*256+128,0);
                        if(building->unknown_slot53(&point,0)) {
                            int strength=building->Type->MaxStrength;
                            building->Strength=strength;
                            building->unknown_70=strength;
                            building->unknown_slot71(2);
                            wasPlaced=true;
                            ++placed;
                            if(nameIndex>17)names.Delete((int)nameIndex);
                        }
                    }
                    ++attempts;
                }
                if(!wasPlaced)delete building;
                ++tries;
            }
            if(placed>=count)break;
        }
    }
}
