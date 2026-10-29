#define RA2_COORD_EQUAL_MEMBER
// AbstractClass *PlanningEventTargets::First_Target_Object() const (0x00617DF0)
// The object of the first set reference (+0x0E, then +0x18, then +0x13), or 0.
#include "shared/planning.hpp"

AbstractClass *PlanningEventTargets::First_Target_Object() const
{
    AbstractClass *object = 0;
    if (Target_0e.Kind) {
        object = Target_0e.As_Abstract();
    } else if (Target_18.Kind) {
        object = Target_18.As_Abstract();
    } else if (Target_13.Kind) {
        object = Target_13.As_Abstract();
    }
    return object;
}
