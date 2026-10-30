// bool MapClass::Build_All_Cliffs(int unused, int region_id) (0x0055B060)
// The map generator's cliff pass (TibSun Build_All_Cliffs): with no generator
// cell data, a temporary array; every record's +0x4A set; the placement
// cursor cleared; every cell offered to Expand_High_Ground (0x0055B210),
// then Place_Cliff (0x0055B820) on the cells with no ramp (+0x11C) and no
// tile (0x0047B590), each pass stopping at the first failure; the pending
// placement object deleted; the temporary array freed. Whether every pass
// succeeded.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_techno.hpp"
#include "shared/map_region.hpp"
// @ref ?Expand_High_Ground@MapClass@@QAE_NPAVCellClass@@H@Z=0055b210
// @ref ?Place_Cliff@MapClass@@QAE_NPAVCellClass@@H@Z=0055b820
// @ref ?Get_Cell_Data_0056dbc0@@YIAAUUnknownMapGenerationCell@@H@Z=0056dbc0
// @ref ?unknown_47b590@CellClass@@QBE_NXZ=0047b590
// @ref ?Unknown_00498F10@DisplayClass@@QAEXPBVCell@@@Z=00498f10
// @ref ?unknown_map_cells_a70a24@@3PAUUnknownMapGenerationCell@@A=00a70a24
// @ref ?unknown_map_cell_side_84e804@@3HA=0084e804

// The generator record of a cell index (TibSun MapRegionClass::Get_Cell_Data; __fastcall).
UnknownMapGenerationCell &__fastcall Get_Cell_Data_0056dbc0(int index);

bool MapClass::Build_All_Cliffs(int unused, int region_id)
{
    bool expanded = true;

    bool is_temp_data = false;
    if (unknown_map_cells_a70a24 == 0) {
        unknown_map_cells_a70a24 = new UnknownMapGenerationCell[unknown_map_cell_side_84e804 * unknown_map_cell_side_84e804];
        is_temp_data = true;
    }

    int r = unknown_map_cell_side_84e804;
    int s = r * r;
    for (int i = 0; i < s; i++) {
        Get_Cell_Data_0056dbc0(i).unknown_45[5] = 1;
    }

    Map.Unknown_00498F10(0);

    Map.Unknown_0055A550();
    CellClass *cellptr = Map.Unknown_0055A490();
    while (cellptr != 0 && expanded) {
        expanded = Expand_High_Ground(cellptr, region_id);
        cellptr = Map.Unknown_0055A490();
    }

    Map.Unknown_0055A550();
    cellptr = Map.Unknown_0055A490();
    while (cellptr != 0 && expanded) {
        if (cellptr->unknown_11c == 0 && cellptr->unknown_47b590()) {
            expanded = Place_Cliff(cellptr, region_id);
        }
        cellptr = Map.Unknown_0055A490();
    }

    ObjectClass *obj = Map.unknown_11a0;
    Map.unknown_11a4 = 0;
    if (obj != 0) {
        delete obj;
        Map.unknown_11a0 = 0;
    }

    if (is_temp_data) {
        delete [] unknown_map_cells_a70a24;
        unknown_map_cells_a70a24 = 0;
    }

    return expanded;
}
