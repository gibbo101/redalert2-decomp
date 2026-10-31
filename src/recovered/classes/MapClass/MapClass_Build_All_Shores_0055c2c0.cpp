// bool MapClass::Build_All_Shores(int region_id, bool set_region) (0x0055C2C0)
// The map generator's water pass (TibSun Build_All_Shores): the placement cursor cleared;
// with no generator cell data, a temporary array; every record's water mask (+0x40) set to
// -1; every cell offered to Expand_Water (0x0055C630), then Prune_Water (0x0055C520), then
// Place_Shore (0x0055CEF0) passes 1 and 2, each pass stopping at the first failure; the
// pending placement object deleted; the temporary array freed. Whether every pass succeeded.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_techno.hpp"
#include "shared/map_region.hpp"
// @ref ?Expand_Water@MapClass@@QAE_NPAVCellClass@@H_N@Z=0055c630
// @ref ?Place_Shore@MapClass@@QAE_NPAVCellClass@@HH_N@Z=0055cef0
// @ref ?Unknown_0055C520@MapClass@@QAEXPAVCellClass@@H_N@Z=0055c520
// @ref ?Get_Cell_Data_0056dbc0@@YIAAUUnknownMapGenerationCell@@H@Z=0056dbc0
// @ref ?Unknown_00498F10@DisplayClass@@QAEXPBVCell@@@Z=00498f10
// @ref ?unknown_map_cells_a70a24@@3PAUUnknownMapGenerationCell@@A=00a70a24
// @ref ?unknown_map_cell_side_84e804@@3HA=0084e804

bool MapClass::Build_All_Shores(int region_id, bool set_region)
{
    Map.Unknown_00498F10(0);

    bool is_temp_data = false;
    if (unknown_map_cells_a70a24 == 0) {
        unknown_map_cells_a70a24 = new UnknownMapGenerationCell[unknown_map_cell_side_84e804 * unknown_map_cell_side_84e804];
        is_temp_data = true;
    }

    int r = unknown_map_cell_side_84e804;
    int s = r * r;
    for (int i = 0; i < s; i++) {
        Get_Cell_Data_0056dbc0(i).unknown_40 = -1;
    }

    Map.Unknown_0055A550();
    CellClass *cellptr = Map.Unknown_0055A490();
    bool expanded = true;
    while (cellptr != 0 && expanded) {
        expanded = Expand_Water(cellptr, region_id, set_region);
        cellptr = Map.Unknown_0055A490();
    }

    Map.Unknown_0055A550();
    cellptr = Map.Unknown_0055A490();
    while (cellptr != 0 && expanded) {
        Unknown_0055C520(cellptr, region_id, set_region);
        cellptr = Map.Unknown_0055A490();
    }

    Map.Unknown_0055A550();
    cellptr = Map.Unknown_0055A490();
    while (cellptr != 0 && expanded) {
        expanded = Place_Shore(cellptr, 1, region_id, set_region);
        cellptr = Map.Unknown_0055A490();
    }

    Map.Unknown_0055A550();
    cellptr = Map.Unknown_0055A490();
    while (cellptr != 0 && expanded) {
        expanded = Place_Shore(cellptr, 2, region_id, set_region);
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
