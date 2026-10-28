// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A490@MapClass@@QAEPAVCellClass@@XZ=0055a490
// @ref ?Unknown_0055A550@MapClass@@QAEXXZ=0055a550
// @ref ?unknown_map_cells_a70a24@@=00a70a24
// @ref ?unknown_map_cell_side_84e804@@=0084e804
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// Operation name and cdecl free-function spelling are hypotheses; original ignores ECX.
void Clear_Map_Cell_Traversal_Marks_00582a50()
{
    Map.Unknown_0055A550();
    for(CellClass *cell=Map.Unknown_0055A490();cell;cell=Map.Unknown_0055A490()) {
        Cell position=cell->MapCoords;
        unknown_map_cells_a70a24[position.Y*unknown_map_cell_side_84e804+position.X].unknown_3c=0;
    }
}
