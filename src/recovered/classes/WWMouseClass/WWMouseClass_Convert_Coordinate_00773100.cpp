// void WWMouseClass::Convert_Coordinate(int &x, int &y) const (0x00773100, slot 17)
// Screen to client coordinates clamped to the confining rectangle (negative y
// is kept when unknown_flag_b2af58 is set).
#include "shared/wwmouse.hpp"
// @ref ?unknown_flag_b2af58@@3_NA=00b2af58

void WWMouseClass::Convert_Coordinate(int &x, int &y) const
{
    x -= ConfiningRect.X;
    y -= ConfiningRect.Y;
    if (x < 0) {
        x = 0;
    }
    if (y < 0 && !unknown_flag_b2af58) {
        y = 0;
    }
    if (x >= ConfiningRect.Width) {
        x = ConfiningRect.Width - 1;
    }
    if (y >= ConfiningRect.Height) {
        y = ConfiningRect.Height - 1;
    }
}
