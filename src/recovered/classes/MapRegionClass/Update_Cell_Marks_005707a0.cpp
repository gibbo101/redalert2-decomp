#include "shared/map.hpp"
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/map_region.hpp"
#include "shared/map_cell.hpp"
#include "shared/unknown_map_generator.hpp"
#include "shared/map_view.hpp"
extern DynamicVectorClass<MapRegionClass *> unknown_map_regions_a6fd28;
// @ref ?unknown_map_regions_a6fd28@@=00a6fd28
// @ref ?Not_Equal_0058db50@Cell@@=0058db50
// @ref ?Create_Region_From_Cell_0056e100@MapRegionClass@@=0056e100

#include "shared/unknown_map_generator.hpp"
#include "shared/map_view.hpp"
// @ref ?Expand_High_Ground@MapClass@@=0055b210
bool UnknownMapGenerator::Expand_All_High_Ground_00583740()
{
    bool success=true;
    Map.Unknown_00498F10(0);
    Map.Unknown_0055A550();
    CellClass *cell=Map.Unknown_0055A490();
    while (cell!=0) {
        if (!success) break;
        success=Map.Expand_High_Ground(cell,-1);
        cell=Map.Unknown_0055A490();
    }
    return success;
}

#include "shared/map_region.hpp"
// @ref ?unknown_map_cells_a70a24@@=00a70a24
// @ref ?unknown_map_cell_side_84e804@@=0084e804
// @ref ?unknown_0056eac0@MapRegionClass@@=0056eac0
void MapRegionClass::Update_Cell_Marks_005707a0()
{
    int count = (int)((unsigned)unknown_map_cell_side_84e804 * (unsigned)unknown_map_cell_side_84e804);
    for (int i = 0; i < count; ++i) unknown_map_cells_a70a24[i].Marked = 0;
    unknown_0056eac0(8, -2);
    for (int j = 0; j < count; ++j) {
        UnknownMapGenerationCell &data=unknown_map_cells_a70a24[j];
        if (data.RegionIndex == Index) unknown_map_cells_a70a24[j].Marked = 1;
        else if (data.RegionIndex == -2) unknown_map_cells_a70a24[j].RegionIndex = Index;
    }
}

// @ref ??8?$VectorClass@USubzoneConnectionStruct@@@@UBE_NABV0@@Z=0040b070
// @ref ?Resize@?$VectorClass@USubzoneConnectionStruct@@@@UAE_NHPBUSubzoneConnectionStruct@@@Z=0040b0b0
// @ref ?Clear@?$VectorClass@USubzoneConnectionStruct@@@@UAEXXZ=0040b1a0
// @ref ?ID@?$VectorClass@USubzoneConnectionStruct@@@@UAEHABUSubzoneConnectionStruct@@@Z=0040b1d0
// @ref ?ID@?$VectorClass@USubzoneConnectionStruct@@@@UAEHPBUSubzoneConnectionStruct@@@Z=0040b210
// @ref ?Fetch@?$VectorClass@USubzoneConnectionStruct@@@@UBE?AUSubzoneConnectionStruct@@H@Z=0040b050
// @ref ?Unknown_00498F10@DisplayClass@@=00498f10
// @ref ?Unknown_0055A550@MapClass@@=0055a550
// @ref ?Unknown_0055A490@MapClass@@=0055a490
