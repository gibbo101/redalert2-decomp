// Point2D __stdcall unknown_zero_point_0042e730() (0x0042E730)
// Returns the point (0, 0) through the hidden result pointer and pops it (ret 4). No callers: a
// __thiscall member returning a Point2D compiles to the same bytes, so the owner (the beacon
// manager's neighbours 0x0042E700/0x0042E740 suggest Unknown84E8D0) and convention are hypotheses.
#include "shared/rect.hpp"

Point2D __stdcall unknown_zero_point_0042e730()
{
    return Point2D(0, 0);
}
