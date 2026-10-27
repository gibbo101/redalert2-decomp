// void MouseClass::Revert_Mouse_Shape() (0x0059F080, slot 20)
// Shows the normal shape again (large form).
#include "shared/mouse_class.hpp"

void MouseClass::Revert_Mouse_Shape()
{
    Override_Mouse_Shape(NormalMouseShape, false);
}
