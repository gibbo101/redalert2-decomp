// int WWMouseClass::Get_Mouse_State() const (0x00771CE0, slot 10)
// The hide nesting state (0 shown, negative hidden).
#include "shared/wwmouse.hpp"

int WWMouseClass::Get_Mouse_State() const
{
    return MouseState;
}
