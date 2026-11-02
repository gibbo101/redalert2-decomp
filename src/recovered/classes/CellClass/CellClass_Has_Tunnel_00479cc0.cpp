// bool CellClass::unknown_479cc0() const (0x00479CC0): Westwood's Has_Tunnel. A tube runs through
// the cell (a valid index into the tube list) and its land is LAND_TUNNEL (10). The named land
// local is the original's /Ob2 size: it keeps the last two Is_Near_Tunnel_NW sites out of line.
#include "shared/cell.hpp"
#include "shared/tube.hpp"

bool CellClass::unknown_479cc0() const
{
    int land = unknown_ec;
    return unknown_116 >= 0 && unknown_116 < unknown_TubeClass_list_008661c8.Count() && land == 10;
}
