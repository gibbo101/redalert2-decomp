// bool MapClass::Rebuild_Shores_At(Cell const &origin) (0x00567490)
// Build_All_Shores (0x0055C2C0) around a cell (TibSun Rebuild_Shores_At): the placement
// cursor cleared; with no generator cell data, a temporary array; every record's +0x4A set
// and water mask (+0x40) set to -1; every cell offered to Expand_Water, then Prune_Water,
// Mark_Fill_Area (0x00567710) on the origin, then Place_Shore passes 1 and 2, each pass
// stopping at the first failure; the pending placement object deleted; +0x4A set again and
// the temporary array freed. Whether every pass succeeded.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_techno.hpp"
#include "shared/map_region.hpp"
// @ref ?Mark_Fill_Area@MapClass@@QAEXABVCell@@_N@Z=00567710

bool MapClass::Rebuild_Shores_At(Cell const &origin)
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
        Get_Cell_Data_0056dbc0(i).unknown_45[5] = 1;
        Get_Cell_Data_0056dbc0(i).unknown_40 = -1;
    }

    Map.Unknown_0055A550();
    CellClass *cellptr = Map.Unknown_0055A490();
    bool expanded = true;
    while (cellptr != 0 && expanded) {
        expanded = Expand_Water(cellptr, 0, 0);
        cellptr = Map.Unknown_0055A490();
    }

    Map.Unknown_0055A550();
    cellptr = Map.Unknown_0055A490();
    while (cellptr != 0 && expanded) {
        Unknown_0055C520(cellptr, 0, 0);
        cellptr = Map.Unknown_0055A490();
    }

    Mark_Fill_Area(origin, true);

    Map.Unknown_0055A550();
    cellptr = Map.Unknown_0055A490();
    while (cellptr != 0 && expanded) {
        expanded = Place_Shore(cellptr, 1, 0, 0);
        cellptr = Map.Unknown_0055A490();
    }

    Map.Unknown_0055A550();
    cellptr = Map.Unknown_0055A490();
    while (cellptr != 0 && expanded) {
        expanded = Place_Shore(cellptr, 2, 0, 0);
        cellptr = Map.Unknown_0055A490();
    }

    ObjectClass *obj = Map.unknown_11a0;
    Map.unknown_11a4 = 0;
    if (obj != 0) {
        delete obj;
        Map.unknown_11a0 = 0;
    }

    for (int j = 0; j < s; j++) {
        Get_Cell_Data_0056dbc0(j).unknown_45[5] = 1;
    }

    if (is_temp_data) {
        delete [] unknown_map_cells_a70a24;
        unknown_map_cells_a70a24 = 0;
    }

    return expanded;
}
