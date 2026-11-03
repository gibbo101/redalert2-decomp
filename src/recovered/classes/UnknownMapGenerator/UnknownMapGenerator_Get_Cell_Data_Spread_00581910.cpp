#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
// The spread that last reached a cell's generator record (TibSun
// MapGeneratorClass::Get_Cell_Data_Spread; ECX owner not read, RET4).
int UnknownMapGenerator::Get_Cell_Data_Spread_00581910(Cell const &cell)
{
    return MapRegionClass::Get_Cell_Data(cell).unknown_3c;
}
