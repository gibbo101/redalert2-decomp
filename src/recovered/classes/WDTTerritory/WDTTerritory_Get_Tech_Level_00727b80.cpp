// int __fastcall (WDTTerritory const *) -- 0x00727B80
// The WDT:TechLevel getter ValueGameOption<unsigned char> reads (Conflict.cpp,
// passed to ValueGameOption::Create by Conflict::Init_Options 0x00727480).
#include "shared/world_domination_tour.hpp"

int __fastcall WDTTerritory_Get_Tech_Level(WDTTerritory const *territory)
{
    return territory->TechLevel;
}
