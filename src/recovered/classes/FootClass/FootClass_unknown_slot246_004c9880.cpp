// int FootClass::unknown_slot246(int arg1 .. int arg9) (0x004C9880)
// Draws the unit (hypothesis: the voxel draw, TechnoClass 0x006D1D00): the
// draw point arg6 (a Point2D) is moved by the locomotor's Draw_Point and
// the transform arg7 is passed as a copy.
#include "shared/foot.hpp"
// @ref ?unknown_slot246@TechnoClass@@UAEHHHHHHHHHH@Z=006d1d00
// @ref __com_issue_error@4=00795940

// The 0x30-byte transform arg7 points at, copied member-wise (12 floats;
// hypothesis: a Matrix3D without the out-of-line copy constructor 0x0058FE10).
struct UnknownDrawMatrix {
    float Values[12];
};

int FootClass::unknown_slot246(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9)
{
    UnknownDrawMatrix matrix = *(UnknownDrawMatrix const *)arg7;
    Point2D point = *(Point2D const *)arg6;
    if (Locomotor != 0) {
        Point2D offset = Locomotor.Checked()->Draw_Point();
        point = Point2D_Sum(*(Point2D const *)arg6, offset);
    }
    return TechnoClass::unknown_slot246(arg1, arg2, arg3, arg4, arg5, (int)&point, (int)&matrix, arg8, arg9);
}
