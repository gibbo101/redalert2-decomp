#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
extern DynamicVectorClass<MapRegionClass *> unknown_map_regions_a6fd28;
// @ref ?unknown_map_regions_a6fd28@@=00a6fd28
// @ref ?unknown_map_region_next_index_a70a28@@=00a70a28
MapRegionClass::MapRegionClass(Cell origin)
    : unknown_00(0), NeighborRegionIndices(0), Index(unknown_map_region_next_index_a70a28),
      CellCount(0), unknown_10(Map[origin].unknown_11b), unknown_14(Map[origin].unknown_47b7e0()),
      Origin(origin), unknown_1a(false), unknown_1b(true), unknown_1c(0), unknown_20(0),
      unknown_24(false), Cells(), Bounds(0,0,0,0)
{
    Cells.Set_Growth_Step(100000);
    unknown_map_region_next_index_a70a28 = (int)((unsigned)unknown_map_region_next_index_a70a28 + 1u);
    unknown_map_regions_a6fd28.Add(this);
}
