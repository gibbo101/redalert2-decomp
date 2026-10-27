// void WWMouseClass::Conditional_Hide_Mouse(Rect region) (0x007730E0, slot 8)
// Hides the mouse regardless of the region.
#include "shared/wwmouse.hpp"

void WWMouseClass::Conditional_Hide_Mouse(Rect)
{
    Hide_Mouse();
}
