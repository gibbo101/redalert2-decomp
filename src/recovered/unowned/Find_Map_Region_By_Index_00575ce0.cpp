#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/map_region.hpp"
extern DynamicVectorClass<MapRegionClass *> unknown_map_regions_a6fd28;
// @ref ?unknown_map_regions_a6fd28@@3V?$DynamicVectorClass@PAVMapRegionClass@@@@A=00a6fd28
MapRegionClass *__fastcall Find_Map_Region_By_Index_00575ce0(int index)
{
    for(int i=0;i<unknown_map_regions_a6fd28.Count();i++)
        if(unknown_map_regions_a6fd28[i]->Index==index)
            return unknown_map_regions_a6fd28[i];
    return 0;
}
