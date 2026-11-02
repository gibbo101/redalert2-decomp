// cell's three screen rectangles (0x004752B0, 0x00474EB0, 0x00475100) moved
// back by the tactical area origin (0x00839630, through Rect::operator- 0x0047D000), and marks the cell for the
// radar (RadarClass 0x00631570).
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/tactical.hpp"
#include "shared/terrain.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_4752b0@CellClass@@QBE?AVRect@@XZ=004752b0
// @ref ?unknown_474eb0@CellClass@@QBE?AVRect@@XZ=00474eb0
// @ref ?unknown_475100@CellClass@@QBE?AVRect@@XZ=00475100

void CellClass::unknown_47c080()
{
    Rect rect = Union(Union(unknown_4752b0(), unknown_474eb0()), unknown_475100());
    unknown_tactical_83996c->Register_Dirty_Area(rect - unknown_rect_839630.Top_Left(), 0);
    Map.Unknown_00631570(MapCoords);
}
