// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A490@MapClass@@QAEPAVCellClass@@XZ=0055a490
// @ref ?Unknown_0055A550@MapClass@@QAEXXZ=0055a550
// @ref ?unknown_map_cells_a70a24@@=00a70a24
// @ref ?unknown_map_cell_side_84e804@@=0084e804
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// Byte wrapping/ordered reads preserved; operation name and free stdcall spelling are hypotheses.
void __stdcall Increment_Other_Region_Cell_Byte_00582ab0(int value,int index)
{
    Map.Unknown_0055A550();
    for(CellClass *cell=Map.Unknown_0055A490();cell;cell=Map.Unknown_0055A490()) {
        Cell position=cell->MapCoords;
        int region=!unknown_map_cells_a70a24 ? -1 : unknown_map_cells_a70a24[position.Y*unknown_map_cell_side_84e804+position.X].RegionIndex;
        if(region!=index)
            cell->unknown_11b+=(unsigned char)value;
    }
}
