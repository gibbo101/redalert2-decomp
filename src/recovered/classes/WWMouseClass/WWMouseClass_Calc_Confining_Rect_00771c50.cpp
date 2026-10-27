// void WWMouseClass::Calc_Confining_Rect() (0x00771C50)
// ConfiningRect = the window's client area in screen coordinates (name from
// the debug string). The explicit return keeps the constructor from expanding
// it inline (without it VC6 inlines it into 0x00771A20).
#include "shared/wwmouse.hpp"
// @ref ??_C@_0CC@EGPP@Calc_Confining_Rect?$CI?$CFd?0?$CFd?0?$CFd?0?$CFd?$CJ@=008013a4
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0

void WWMouseClass::Calc_Confining_Rect()
{
    RECT rect;
    GetClientRect(Window, &rect);
    POINT topleft;
    topleft.x = rect.left;
    topleft.y = rect.top;
    ClientToScreen(Window, &topleft);
    POINT bottomright;
    bottomright.x = rect.right;
    bottomright.y = rect.bottom;
    ClientToScreen(Window, &bottomright);
    ConfiningRect = Rect(topleft.x, topleft.y, bottomright.x - topleft.x, bottomright.y - topleft.y);
    Debug_Printf("Calc_Confining_Rect(%d,%d,%d,%d)\n", topleft.x, topleft.y, bottomright.x - topleft.x,
                 bottomright.y - topleft.y);
    return;
}
