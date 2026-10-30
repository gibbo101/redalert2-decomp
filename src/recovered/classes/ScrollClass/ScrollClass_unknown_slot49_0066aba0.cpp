// void ScrollClass::unknown_slot49(Point2D const &xy) (0x0066ABA0, slot 49)
// Ends a pending scroll by restoring the default mouse; otherwise the
// display's slot 49.
#include "shared/scroll.hpp"
// @ref ?unknown_flag_83740c@@3_NA=0083740c
// @ref ?unknown_slot49@DisplayClass@@UAEXABUPoint2D@@@Z=0049af90

void ScrollClass::unknown_slot49(Point2D const &xy)
{
    if (unknown_4f28) {
        Set_Default_Mouse(0, unknown_flag_83740c);
        unknown_4f28 = false;
        return;
    }
    DisplayClass::unknown_slot49(xy);
}
