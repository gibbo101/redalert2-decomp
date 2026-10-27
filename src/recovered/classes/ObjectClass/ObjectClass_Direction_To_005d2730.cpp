// Existing ObjectClass direct Aircraft dependency; source spelling is a hypothesis.
#include "shared/object.hpp"
#include "shared/facing.hpp"
#include "shared/fast_math.hpp"
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
static inline UnknownFacingDir Object_Geometry_Direction_005D2730(CoordStruct const &origin, CoordStruct const &destination)
{
    int origin_x = origin.X;
    int destination_x = destination.X;
    return UnknownFacingDir((unsigned short)((Fast_Atan2((double)origin.Y - destination.Y,
        (double)destination_x - origin_x) - 1.5707963267948966) * -10430.060040584269));
}
UnknownFacingDir ObjectClass::Direction_To(AbstractClass const *target) const
{
    return Object_Geometry_Direction_005D2730(Center_Coord(), target->Center_Coord());
}
