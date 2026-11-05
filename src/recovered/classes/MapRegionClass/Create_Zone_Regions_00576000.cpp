// void __fastcall MapRegionClass::Create_Zone_Regions_00576000(int zone_kind, int zone) (0x00576000): discards every
// region, then makes one (Create_Zone_Region_00575d20) for each unclaimed in-bounds map cell with no +0x4C occupant
// that lies in the given zone. Not in TibSun.
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Create_Zone_Region_00575d20@MapRegionClass@@SIXPAVCellClass@@HH@Z=00575d20

static inline bool Zone_Cell_In_Bounds(Cell const &cell)
{
    int x = cell.X;
    int y = cell.Y;
    return y + x > unknown_map_min_a70a1c && x - y < unknown_map_min_a70a1c &&
        y - x < unknown_map_min_a70a1c && y + x <= unknown_map_max_a70a20;
}

void __fastcall MapRegionClass::Create_Zone_Regions_00576000(int zone_kind, int zone)
{
    Destroy_Cell_Regions();
    Map.Unknown_0055A550();
    for (CellClass *cell = Map.Unknown_0055A490(); cell; cell = Map.Unknown_0055A490()) {
        Cell const &position = cell->MapCoords;
        if (Zone_Cell_In_Bounds(cell->MapCoords)) {
            if (Get_Cell_Data(position).RegionIndex == -1 && cell->unknown_4c == 0 &&
                Map.Zone(position, zone_kind, false) == zone) {
                Create_Zone_Region_00575d20(cell, zone_kind, zone);
            }
        }
    }
}
