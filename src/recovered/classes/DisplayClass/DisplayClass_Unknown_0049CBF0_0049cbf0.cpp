// bool DisplayClass::Unknown_0049CBF0(CoordStruct const &coord, bool alt) (0x0049CBF0)
// Asks the map's cell at a coordinate whether the sub-cell spot of the
// coordinate is free (0x00476460), alt being its second argument.
#include "shared/display.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_004763D0@@YIHABUCoordStruct@@@Z=004763d0
// @ref ?unknown_476460@CellClass@@QBE_NH_N@Z=00476460
// @ref ??AMapClass@@QAEAAVCellClass@@ABUCoordStruct@@@Z=00548000

int __fastcall Unknown_004763D0(CoordStruct const &coord);

bool DisplayClass::Unknown_0049CBF0(CoordStruct const &coord, bool alt)
{
    return Map[coord].unknown_476460(Unknown_004763D0(coord), alt);
}
