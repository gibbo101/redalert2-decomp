// Rect MSShapeAnim::Get_Rect() (0x005ACD00)
// Screen rectangle of the current frame; centred on X/Y with flag 0x200.
#include "shared/ms_anim.hpp"
// @ref _unknown_empty_rect=00a71808

Rect MSShapeAnim::Get_Rect()
{
    ShapeFileStruct *shape = Shape;
    Rect rect = shape->Get_Frame_Rect(Frame);
    rect.X = X + rect.X;
    rect.Y = Y + rect.Y;
    if (Flags & 0x200) {
        rect.X -= shape->Width / 2;
        rect.Y -= shape->Height / 2;
    }
    return rect;
}
