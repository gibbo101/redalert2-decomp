// void MSOverlayAnim::Draw(Surface *surface, Rect const *clip) (0x005AD6B0, slot 5)
// As MSFadeAnim::Draw while unknown_0C is set, the fade level capped at 3.
#include "shared/ms_anim.hpp"
// @ref _unknown_empty_rect=00a71808

void MSOverlayAnim::Draw(Surface *surface, Rect const *clip)
{
    Rect area(0, 0, 0, 0);
    if (unknown_0C) {
        ShapeFileStruct *shape = Shape;
        area = shape->Get_Frame_Rect(Frame);
        area.X = X + area.X;
        area.Y = Y + area.Y;
        if (Flags & 0x200) {
            area.X -= shape->Width / 2;
            area.Y -= shape->Height / 2;
        }
        if (clip != 0) {
            area = clip->Intersect(area);
            if (!area.Is_Valid()) {
                return;
            }
        }
        unsigned level = (unsigned)unknown_40 < 3 ? unknown_40 : 3;
        CC_Draw_Shape(surface, Drawer, Shape, Frame, Point2D(X, Y), surface->Get_Rect(),
                      unknown_fade_flags_7e57f0[level] | Flags, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
    }
}
