// @ref __real@8@3fe1e0000000e0000000=007a6038
// @ref __real@8@3fe28000000080000000=007a6048
#include "shared/unknown_map_generator.hpp"
#include "shared/building_view.hpp"
#include "shared/unit.hpp"
#include "shared/infantry.hpp"
#include "shared/infantry_type.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
extern char const unknown_neutral_name_7e14b8[];
extern char const *unknown_urban_unit_names_7e0c30[];
unsigned __fastcall Map_Random_Range_005797a0(unsigned,unsigned);
// @ref ?unknown_neutral_name_7e14b8@@=007e14b8
// @ref ?unknown_urban_unit_names_7e0c30@@=007e0c30
// @ref ?Map_Random_Range_005797a0@@=005797a0
void UnknownMapGenerator::Generate_Urban_Units_00588100(DynamicVectorClass<Cell> &cells)
{
    HouseClass *neutral=HouseClass::As_Pointer(HouseTypeClass::Find_Index(unknown_neutral_name_7e14b8));
    int count=Map_Random_Range_005797a0(1,5);
    int tries=0;
    int placed=0;
    if(count>0) {
    while(true) {
        if(tries>=2*count)break;
        int nameIndex=Map_Random_Range_005797a0(0,6);
        FootClass *unit;
        if(nameIndex<=2)unit=new InfantryClass(InfantryTypes[InfantryTypeClass::From_Name(unknown_urban_unit_names_7e0c30[nameIndex])],neutral);
        else unit=new UnitClass(UnitTypes[UnitTypeClass::From_Name(unknown_urban_unit_names_7e0c30[nameIndex])],neutral);
        int attempts=0;
        bool wasPlaced=false;
        while(!wasPlaced) {
            if(attempts>=60)break;
            Cell position=cells[Map_Random_Range_005797a0(0,cells.Count()-1)];
            if(Map.Unknown_0055A660(position,true) && Map[position].OccupierPtr==0) {
                if(unit->unknown_slot53(&CoordStruct(position.X*256+128,position.Y*256+128,0),Map_Random_Range_005797a0(0,7)*32)) {
                    int strength=unit->unknown_slot32()->MaxStrength;
                    unit->Strength=strength;
                    unit->unknown_70=strength;
                    unit->unknown_slot71(2);
                    wasPlaced=true;
                    ++placed;
                }
            }
            ++attempts;
        }
        if(!wasPlaced)delete unit;
        ++tries;
        if(placed>=count)break;
    }
    }
}
