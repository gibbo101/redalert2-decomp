// void ScrollClass::unknown_slot44(Point2D const &point) (0x0066ABE0, slot 44)
// Unless 0x00A40D44 is set: the display's slot 44, remembering point, then
// shows the mouse.
#include "shared/scroll.hpp"
#include "shared/mouse.hpp"
// @ref ?unknown_flag_a40d44@@3_NA=00a40d44
// @ref ?unknown_slot44@DisplayClass@@UAEXABUPoint2D@@@Z=0049af80
// @ref ?WWMouse@@3PAVMouse@@A=00839c68

void ScrollClass::unknown_slot44(Point2D const &point)
{
    if (!unknown_flag_a40d44) {
        DisplayClass::unknown_slot44(point);
        unknown_4f20.X = point.X;
        unknown_4f20.Y = point.Y;
        unknown_4f28 = false;
        WWMouse->Show_Mouse();
    }
}
