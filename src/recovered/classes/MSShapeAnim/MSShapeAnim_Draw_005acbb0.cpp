// void MSShapeAnim::Draw(Surface *surface, Rect const *clip) (0x005ACBB0, slot 5)
// Draws the current frame at X, Y unless clip is given and the frame's screen
// rectangle (Get_Rect's body, spelled out) lies outside it.
#include "shared/ms_anim.hpp"
// @ref _unknown_empty_rect=00a71808

void MSShapeAnim::Draw(Surface *surface, Rect const *clip)
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
    if (unknown_0C) {
        CC_Draw_Shape(surface, Drawer, Shape, Frame, Point2D(X, Y), surface->Get_Rect(), Flags | 0x400, 0, 0, 0, 1000,
                      0, 0, Point2D(0, 0));
    }
}
