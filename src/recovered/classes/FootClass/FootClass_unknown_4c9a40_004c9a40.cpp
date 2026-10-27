// void FootClass::unknown_4c9a40(int arg1 .. int arg11) (0x004C9A40)
// Draws the unit's shadow (hypothesis): when the locomotor casts one
// (ILocomotion::Is_To_Have_Shadow), the draw point arg6 (a Point2D) moves by
// the locomotor's Shadow_Point and TechnoClass 0x006D21E0 draws.
#include "shared/foot.hpp"
// @ref ?Unknown_006D21E0@TechnoClass@@QAEHHHHHHHHHHHH@Z=006d21e0
// @ref __com_issue_error@4=00795940

void FootClass::unknown_4c9a40(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11)
{
    if (Locomotor != 0 && Locomotor.Checked()->Is_To_Have_Shadow() == true) {
        Point2D point = *(Point2D const *)arg6;
        if (Locomotor != 0) {
            Point2D offset = Locomotor.Checked()->Shadow_Point();
            point = Point2D_Sum(*(Point2D const *)arg6, offset);
        }
        Unknown_006D21E0(arg1, arg2, arg3, arg4, arg5, (int)&point, arg7, arg8, arg9, arg10, arg11);
    }
}
