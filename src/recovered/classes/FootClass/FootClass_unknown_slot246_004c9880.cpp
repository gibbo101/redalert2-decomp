// Typed voxel-draw ABI; original nine stack arguments and RET36. (0x004C9880)
// Draws the unit (hypothesis: the voxel draw, TechnoClass 0x006D1D00): the
// draw point arg6 (a Point2D) is moved by the locomotor's Draw_Point and
// the transform arg7 is passed as a copy.
#include "shared/foot.hpp"

// @ref __com_issue_error@4=00795940

// The 0x30-byte transform arg7 points at, copied member-wise (12 floats;
// hypothesis: a Matrix3D without the out-of-line copy constructor 0x0058FE10).
struct UnknownDrawMatrix {
    float Values[12];
};

void FootClass::unknown_slot246(UnknownObjectPair const &voxel, int frame, int key, UnknownBuffer *cache, Rect const &cliprect, Point2D const &draw_point, Matrix3D const &transform, int brightness, unsigned flags)
{
    UnknownDrawMatrix matrix = *(UnknownDrawMatrix const *)&transform;
    Point2D point = draw_point;
    if (Locomotor != 0) {
        Point2D offset = Locomotor.Checked()->Draw_Point();
        point = Point2D_Sum(draw_point, offset);
    }
    TechnoClass::unknown_slot246(voxel, frame, key, cache, cliprect, point, *(Matrix3D const *)&matrix, brightness, flags);
}
// @ref ?unknown_slot246@TechnoClass@@UAEXABVUnknownObjectPair@@HHPAVUnknownBuffer@@ABVRect@@ABUPoint2D@@ABVMatrix3D@@HI@Z=006d1d00
