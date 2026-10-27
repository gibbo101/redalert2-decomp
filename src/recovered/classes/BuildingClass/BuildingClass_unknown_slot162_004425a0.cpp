// UnknownFacingDir BuildingClass::unknown_slot162() (0x004425A0, slot 162)
// The direction from this center towards the object at +0x228 unless
// slot 232 holds or there is none; otherwise the current facing at +0x2E0.
#include "shared/building.hpp"
#include "shared/fast_math.hpp"
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
// @ref ?Current@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8be0
// @ref __ftol=0077f110

// The direction from one coordinate to another (an inline helper;
// hypothesis: Westwood's Direction()).
static inline UnknownFacingDir Coord_Direction(CoordStruct const &from, CoordStruct const &to)
{
    int fx = from.X;
    int tx = to.X;
    double angle = Fast_Atan2((double)from.Y - to.Y, (double)tx - fx);
    return UnknownFacingDir((unsigned short)(int)((angle - 1.5707963267948966) * -10430.060040584269));
}

UnknownFacingDir BuildingClass::unknown_slot162()
{
    if (!unknown_slot232() && unknown_228) {
        return Coord_Direction(Center_Coord(), unknown_228->Center_Coord());
    }
    return unknown_2e0.Current();
}
