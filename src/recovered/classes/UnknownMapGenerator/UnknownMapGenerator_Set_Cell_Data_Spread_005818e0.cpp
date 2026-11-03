#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
// Marks a cell's generator record as reached by the spread patch_id (TibSun
// MapGeneratorClass::Set_Cell_Data_Spread; ECX owner not read, RET8).
void UnknownMapGenerator::Set_Cell_Data_Spread_005818e0(Cell const &cell,int patch_id)
{
    MapRegionClass::Get_Cell_Data(cell).unknown_3c=patch_id;
}
