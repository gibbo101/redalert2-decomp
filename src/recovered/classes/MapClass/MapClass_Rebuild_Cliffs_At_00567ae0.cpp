// bool MapClass::Rebuild_Cliffs_At(Cell const &cell) (0x00567AE0)
// Build_All_Cliffs (0x0055B060) around a cell (TibSun Rebuild_Cliffs_At):
// the generator records' +0x4A set (unless the array is made here), every
// cell offered to Expand_High_Ground with region 0, Mark_Fill_Area
// (0x00567710) on the cell, then Place_Cliff on the bare cells, the pending
// placement object deleted, +0x4A set again and a temporary array freed.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_techno.hpp"
#include "shared/map_region.hpp"
// @ref ?Mark_Fill_Area@MapClass@@QAEXABVCell@@_N@Z=00567710

bool MapClass::Rebuild_Cliffs_At(Cell const &cell)
{
    int s = unknown_map_cell_side_84e804 * unknown_map_cell_side_84e804;
    bool expanded = true;

    bool is_temp_data = false;
    if (unknown_map_cells_a70a24 == 0) {
        unknown_map_cells_a70a24 = new UnknownMapGenerationCell[s];
        is_temp_data = true;
    } else {
        for (int i = 0; i < s; i++) {
            Get_Cell_Data_0056dbc0(i).unknown_45[5] = 1;
        }
    }

    Map.Unknown_00498F10(0);

    Map.Unknown_0055A550();
    CellClass *cellptr = Map.Unknown_0055A490();
    while (cellptr != 0 && expanded) {
        expanded = Expand_High_Ground(cellptr, 0);
        cellptr = Map.Unknown_0055A490();
    }

    Mark_Fill_Area(cell, false);

    Map.Unknown_0055A550();
    cellptr = Map.Unknown_0055A490();
    while (cellptr != 0 && expanded) {
        if (cellptr->unknown_11c == 0 && cellptr->unknown_47b590()) {
            expanded = Place_Cliff(cellptr, 0);
        }
        cellptr = Map.Unknown_0055A490();
    }

    ObjectClass *obj = Map.unknown_11a0;
    Map.unknown_11a4 = 0;
    if (obj != 0) {
        delete obj;
        Map.unknown_11a0 = 0;
    }

    for (int i = 0; i < s; i++) {
        Get_Cell_Data_0056dbc0(i).unknown_45[5] = 1;
    }

    if (is_temp_data) {
        delete [] unknown_map_cells_a70a24;
        unknown_map_cells_a70a24 = 0;
    }

    return expanded;
}
