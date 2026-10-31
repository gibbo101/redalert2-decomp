// void FootClass::unknown_4c9a40(int arg1 .. int arg11) (0x004C9A40)
// Draws the unit's shadow (hypothesis): when the locomotor casts one
// (ILocomotion::Is_To_Have_Shadow), the draw point arg6 (a Point2D) moves by
// the locomotor's Shadow_Point and TechnoClass 0x006D21E0 draws.
#include "shared/foot.hpp"

// @ref __com_issue_error@4=00795940

void FootClass::unknown_4c9a40(UnknownObjectPair const &voxel, int layer, int key, UnknownBuffer *cache, Rect const &cliprect, Point2D const &draw_point, Matrix3D const &transform, bool force_cache, unsigned unknown_1, unsigned unknown_2, unsigned unknown_3)
{
    if (Locomotor != 0 && Locomotor.Checked()->Is_To_Have_Shadow() == true) {
        Point2D point = draw_point;
        if (Locomotor != 0) {
            Point2D offset = Locomotor.Checked()->Shadow_Point();
            point = Point2D_Sum(draw_point, offset);
        }
        Unknown_006D21E0(voxel, layer, key, cache, cliprect, point, transform, force_cache, unknown_1, unknown_2, unknown_3);
    }
}
// @ref ?Unknown_006D21E0@TechnoClass@@QAEXABVUnknownObjectPair@@HHPAVUnknownBuffer@@ABVRect@@ABUPoint2D@@ABVMatrix3D@@_NIII@Z=006d21e0
