// void MSFadeAnim::Draw(Surface *surface, Rect const *clip) (0x005AD210, slot 5)
// As MSShapeAnim::Draw, with the translucency flags of fade level unknown_40
// (the last level past 3) and no unknown_0C test.
#include "shared/ms_anim.hpp"
// @ref _unknown_empty_rect=00a71808

void MSFadeAnim::Draw(Surface *surface, Rect const *clip)
{
    Rect area(0, 0, 0, 0);
    if (clip != 0) {
        ShapeFileStruct *shape = Shape;
        area = shape->Get_Frame_Rect(Frame);
        area.X = X + area.X;
        area.Y = Y + area.Y;
        if (Flags & 0x200) {
            area.X -= shape->Width / 2;
            area.Y -= shape->Height / 2;
        }
        area = clip->Intersect(area);
        if (!area.Is_Valid()) {
            return;
        }
    }
    int flags;
    if ((unsigned)unknown_40 < 4) {
        flags = unknown_fade_flags_7e57f0[unknown_40] | Flags;
    } else {
        flags = Flags | unknown_fade_flags_7e57f0[3];
    }
    CC_Draw_Shape(surface, Drawer, Shape, Frame, Point2D(X, Y), surface->Get_Rect(), flags, 0, 0, 0, 1000, 0, 0,
                  Point2D(0, 0));
}
