// void WWMouseClass::Get_Cursor_Position(int &x, int &y) (0x00773160)
// The Windows cursor position in client coordinates. Never called (inlined into
// Process_Mouse); name is a hypothesis.
#include "shared/wwmouse.hpp"

void WWMouseClass::Get_Cursor_Position(int &x, int &y)
{
    POINT point;
    GetCursorPos(&point);
    x = point.x;
    y = point.y;
    Convert_Coordinate(x, y);
}
