// Region fill operation/bool-or-char return/free-stdcall intent remain hypotheses.
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/map_region.hpp"
#include "shared/tileset_index.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A490@MapClass@@QAEPAVCellClass@@XZ=0055a490
// @ref ?Unknown_0055A550@MapClass@@QAEXXZ=0055a550
// @ref ?unknown_map_cells_a70a24@@=00a70a24
// @ref ?unknown_map_cell_side_84e804@@=0084e804
// @ref ?unknown_tileset_a52c60@@=00a52c60
bool __stdcall Fill_Empty_Region_Tiles_0057dfe0(int index)
{
    Map.Unknown_0055A550();
    for(CellClass *cell=Map.Unknown_0055A490();cell;cell=Map.Unknown_0055A490()) {
        int region=!unknown_map_cells_a70a24 ? -1 : unknown_map_cells_a70a24[cell->MapCoords.Y*unknown_map_cell_side_84e804+cell->MapCoords.X].RegionIndex;
        if(region==index && (cell->IsoTileIndex==0 || cell->IsoTileIndex==0xffff))
            cell->IsoTileIndex=unknown_tileset_a52c60;
    }
    return 1;
}
