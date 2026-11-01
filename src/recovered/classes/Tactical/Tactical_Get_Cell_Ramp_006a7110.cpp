// Existing006A7110: originalTacticalreceiver supported by callerECX and reference.
#include "shared/cell_class.hpp"
#include "shared/tactical.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABUCoordStruct@@@Z=00548000
int Tactical::Get_Cell_Ramp_006a7110(CoordStruct const &coord)
{
    return Map[coord].unknown_11c;
}
