// void MouseClass::Init_Clear() (0x0059F510, slot 7)
// After the sidebar's, back to the large default shape.
#include "shared/mouse_class.hpp"
// @ref ?Init_Clear@SidebarClass@@UAEXXZ=0067b8b0

void MouseClass::Init_Clear()
{
    ScrollClass::Init_Clear();
    IsSmall = false;
    NormalMouseShape = 0;
}
