// void MSShapeAnim::Set_Frame(int frame) (0x005AC760)
// Changes the frame, reports the old rectangle as dirty when the new one
// differs, and clamps to the last frame.
#include "shared/ms_anim.hpp"
#include "shared/dsurface.hpp"
// @ref ?unknown_surface_839954@@3PAVSurface@@A=00839954
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958

void MSShapeAnim::Set_Frame(int frame)
{
    Rect old = Get_Rect();
    Frame = frame;
    if (old != Get_Rect()) {
        unknown_surface_839954->Copy_From(old, *unknown_surface_839958, old, false, true);
    }
    if (Frame >= (unsigned)Shape->FrameCount) {
        Frame = Shape->FrameCount - 1;
    }
}
