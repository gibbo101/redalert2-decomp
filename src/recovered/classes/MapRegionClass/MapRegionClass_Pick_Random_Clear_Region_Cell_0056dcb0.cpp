// Cell MapRegionClass::Pick_Random_Clear_Region_Cell_0056dcb0() (0x0056DCB0): up to 200 random cells of this
// region (Pick_Random_Region_Cell_0056dc20, inline) until the map cell passes unknown_47b590; else (0,0).
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_47b590@CellClass@@QBE_NXZ=0047b590

Cell MapRegionClass::Pick_Random_Clear_Region_Cell_0056dcb0()
{
    int tries = 0;
    for (;;) {
        Cell position = Pick_Random_Region_Cell_0056dc20();
        if (++tries > 200) {
            return Cell(0, 0);
        }
        if (Map[position].unknown_47b590()) {
            return position;
        }
    }
}
