// Operation/free-cdecl spelling remain hypotheses; original entry is explicitly unreferenced.
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/map_region.hpp"
extern double const unknown_map_default_007a5d28;
extern double const unknown_map_default_007a5d30;
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A490@MapClass@@QAEPAVCellClass@@XZ=0055a490
// @ref ?Unknown_0055A550@MapClass@@QAEXXZ=0055a550
// @ref ?unknown_map_cells_a70a24@@=00a70a24
// @ref ?unknown_map_cell_side_84e804@@=0084e804
// @ref ?unknown_map_default_007a5d28@@=007a5d28
// @ref ?unknown_map_default_007a5d30@@=007a5d30
void Initialize_Grid_Thresholds_00585240()
{
    Map.Unknown_0055A550();
    for(CellClass *cell=Map.Unknown_0055A490();cell;cell=Map.Unknown_0055A490()) {
        Cell position=cell->MapCoords;
        UnknownMapGenerationCell &target=unknown_map_cells_a70a24[position.Y*unknown_map_cell_side_84e804+position.X];
        target.unknown_28=unknown_map_default_007a5d28;
        target.unknown_20=unknown_map_default_007a5d30;
    }
}
