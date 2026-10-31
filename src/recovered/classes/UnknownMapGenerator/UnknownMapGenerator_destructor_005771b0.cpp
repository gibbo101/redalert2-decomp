// @ref ?Clear@?$VectorClass@PBVBuildingTypeClass@@@@UAEXXZ=004f7100
#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
#include "shared/map_preview.hpp"
extern DynamicVectorClass<MapRegionClass *> unknown_map_regions_a6fd28;
// @ref ??1UnknownMapGenerator@@QAE@XZ=005771b0
// @ref ??1MapRegionClass@@QAE@XZ=0056d970
// @ref ??1UnknownPreview_0061D430@@QAE@XZ=0061d440
UnknownMapGenerator::~UnknownMapGenerator()
{
    MapRegionClass::Destroy_Cell_Regions();
    if(unknown_map_cells_a70a24!=0) {
        delete[] unknown_map_cells_a70a24;
        unknown_map_cells_a70a24=0;
    }
    if(unknown_178!=0) {
        delete reinterpret_cast<MapSeedClass *>(unknown_178);
        unknown_178=0;
    }
    if(unknown_17c!=0) {
        delete reinterpret_cast<UnknownPreview_0061D430 *>(unknown_17c);
        unknown_17c=0;
    }
}
