// @ref __real@8@40028000000000000000=0079d558
// @ref __real@8@3fe1a0000000a0000000=007a5ff0
// @ref __real@8@3fe2f0000000f0000000=007a6058
#include "shared/unknown_map_generator.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/building_view.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/building_type_list.hpp"
extern char *unknown_rural_building_names_7e0c60[36];
extern char const unknown_neutral_name_7e14b8[];
unsigned __fastcall Map_Random_Range_005797a0(unsigned,unsigned);
// @ref ?unknown_rural_building_names_7e0c60@@=007e0c60
// @ref ?unknown_neutral_name_7e14b8@@=007e14b8
// @ref ?Map_Random_Range_005797a0@@=005797a0
void UnknownMapGenerator::Generate_Rural_Buildings_00589ac0(Cell const &origin)
{
    int count=Map_Random_Range_005797a0(8,12);
    int tries=0;
    int placed=0;
    int height=Map[origin].unknown_11b;
    unsigned first=0;
    unsigned last=35;
    if(SeedOptions.Theater==0)first=15;
    DynamicVectorClass<char *> names;
    for(int index=0;index<36;++index)names.Add(unknown_rural_building_names_7e0c60[index]);
    HouseClass *neutral=HouseClass::As_Pointer(HouseTypeClass::Find_Index(unknown_neutral_name_7e14b8));
    if(count>0) {
        while(true) {
            if(tries>=2*count)break;
            unsigned nameIndex=Map_Random_Range_005797a0(first,last);
            int typeIndex=BuildingTypeClass::From_Name(names[nameIndex]);
            if(typeIndex!=-1) {
                BuildingClass *building=new BuildingClass(BuildingTypes[typeIndex],neutral);
                int attempts=0;
                bool wasPlaced=false;
                while(!wasPlaced) {
                    if(attempts>=60)break;
                    Cell position=origin.unknown_42add0(Cell(Map_Random_Range_005797a0(0,14)-7,Map_Random_Range_005797a0(0,14)-7));
                    Cell const *list=building->Type->unknown_slot36(1);
                    bool clear=true;
                    while(list->X!=0x7fff || list->Y!=0x7fff) {
                        Cell next=position.unknown_42add0(*list);
                        CellClass *cell=&Map[next];
                        if(cell->OccupierPtr!=0 || !cell->unknown_47b590() || cell->unknown_11b!=height || cell->unknown_ec==3 || !Map.Unknown_0055A740(cell,true))clear=false;
                        ++list;
                        if(!clear)break;
                    }
                    if(clear) {
                        CoordStruct point(position.X*256+128,position.Y*256+128,0);
                        if(building->unknown_slot53(&point,0)) {
                            wasPlaced=true;
                            ++placed;
                            names.Delete((int)nameIndex);
                            --last;
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
