// Existing Object placement interface; semantic names are hypotheses.
#include "shared/infantry.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_facing_offsets_851ac0@@3QBUUnknownFacingOffset@@B=00851ac0
// @ref ?Map@@3VMouseClass@@A=008324e0
static inline CoordStruct Object_Translation_005D2D60(UnknownFacingOffset const &offset, CoordStruct origin)
{
    return CoordStruct((int)((unsigned int)origin.X + (unsigned int)offset.X),
        (int)((unsigned int)origin.Y + (unsigned int)offset.Y), origin.Z);
}
void ObjectClass::unknown_slot100(int facing)
{
    unknown_slot71(0);
    CoordStruct destination = Object_Translation_005D2D60(unknown_facing_offsets_851ac0[facing & 7], Coord);
    if (unknown_slot101(&Map[destination], facing, -1, 0, 1) == 0) unknown_slot103(destination);
    unknown_slot71(1);
}
