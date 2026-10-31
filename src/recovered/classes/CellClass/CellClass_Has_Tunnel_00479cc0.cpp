// bool CellClass::unknown_479cc0() const (0x00479CC0): Westwood's Has_Tunnel. A tube runs through
// the cell (a valid index into the tube list) and its land is LAND_TUNNEL (10).
#include "shared/cell.hpp"
#include "shared/tube.hpp"

bool CellClass::unknown_479cc0() const
{
    return unknown_116 >= 0 && unknown_116 < unknown_TubeClass_list_008661c8.Count() && unknown_ec == 10;
}
