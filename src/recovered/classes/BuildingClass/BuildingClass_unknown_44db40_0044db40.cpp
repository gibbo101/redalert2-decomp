// bool BuildingClass::unknown_44db40(CellClass *cell) (0x0044DB40)
// Whether the distance from the building's centre to the cell's centre is
// at most the type's PsychicDetectionRadius in cells (256 leptons each).
#include "shared/building.hpp"
#include "shared/cell.hpp"
// @ref ?unknown_475d60@CellClass@@QBE?AUCoordStruct@@XZ=00475d60
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref __ftol=0077f110

bool BuildingClass::unknown_44db40(CellClass *cell)
{
    CoordStruct here = Center_Coord();
    CoordStruct there = cell->unknown_475d60();
    return Coord_Distance(here, there) <= Type->PsychicDetectionRadius << 8;
}
