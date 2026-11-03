// @ref __real@8@3fe38800000088000000=007a6060
// @ref __real@8@3fe28000000080000000=007a6048
// @ref __real@8@3fe18000000080000000=007a5f78
#include "shared/unknown_map_generator.hpp"
#include "shared/building.hpp"
#include "shared/unit.hpp"
#include "shared/infantry_type.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
extern char const unknown_neutral_name_7e14b8[];
extern char const *unknown_rural_unit_names_7e0cf0[6];
unsigned __fastcall Map_Random_Range_005797a0(unsigned,unsigned);
// @ref ?unknown_neutral_name_7e14b8@@=007e14b8
// @ref ?unknown_rural_unit_names_7e0cf0@@=007e0cf0
// @ref ?Map_Random_Range_005797a0@@=005797a0
void UnknownMapGenerator::Generate_Rural_Units_00589f00(Cell const &origin)
{
    HouseClass *neutral=HouseClass::As_Pointer(HouseTypeClass::Find_Index(unknown_neutral_name_7e14b8));
    int count=Map_Random_Range_005797a0(1,4);
    int tries=0;
    int placed=0;
    while(placed<count) {
        if(tries>=2*count)break;
        int nameIndex=Map_Random_Range_005797a0(0,5);
        ObjectClass *unit;
        if(nameIndex<=2)unit=new InfantryClass(InfantryTypes[InfantryTypeClass::From_Name(unknown_rural_unit_names_7e0cf0[nameIndex])],neutral);
        else unit=new UnitClass(UnitTypes[UnitTypeClass::From_Name(unknown_rural_unit_names_7e0cf0[nameIndex])],neutral);
        int attempts=0;
        bool wasPlaced=false;
        while(!wasPlaced) {
            if(attempts>=60)break;
            Cell position=origin + Cell(Map_Random_Range_005797a0(0,16)-8,Map_Random_Range_005797a0(0,16)-8);
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
    }
}
