// int AnimClass::unknown_slot45() const (0x00420D70)
// The base value (ObjectClass slot 45, a sort height) plus YSortAdjust.
#include "shared/anim.hpp"

int AnimClass::unknown_slot45() const
{
    return ObjectClass::unknown_slot45() + YSortAdjust;
}
