// void AnimClass::Detach(AbstractClass *target, bool all) (0x00422B20)
// Drops references to a removed object; losing the attached object
// detaches the animation from the map and ends it (slot 71).
#include "shared/anim.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

void AnimClass::Detach(AbstractClass *target, bool all)
{
    ObjectClass::Detach(target, all);
    if (unknown_b4 == target) {
        Map.Remove(this);
        unknown_b4 = 0;
        unknown_17b = true;
        unknown_slot71(0);
    }
    if (Class == target) {
        Class = 0;
    }
    if (unknown_15c == target) {
        unknown_15c = 0;
        unknown_slot60();
    }
}
