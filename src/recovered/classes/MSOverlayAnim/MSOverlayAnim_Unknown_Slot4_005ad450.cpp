// bool MSOverlayAnim::Unknown_Slot4(Surface *surface, Rect *dirty) (0x005AD450, slot 4)
// While the fade level is below 4, every unknown_24 ticks redraws the current
// frame at the next fade level over the restored background and the other
// animations of Anims, reporting its area; at level 4 the frame is also drawn
// into the background surface. Returns !unknown_48.
#include "shared/ms_anim.hpp"
// @ref _unknown_empty_rect=00a71808
// @ref ??0Rect@@QAE@HHHH@Z=0042bcd0

bool MSOverlayAnim::Unknown_Slot4(Surface *surface, Rect *dirty)
{
    if (unknown_0C == true && Timer.Value() == 0) {
        Timer = CDTimerClass<SystemTimerClass>(unknown_24);
        if ((unsigned)unknown_40 < 4) {
            *dirty = Frame_Rect();
            dirty->X = X + dirty->X;
            dirty->Y = Y + dirty->Y;
            if (Flags & 0x200) {
                dirty->X -= Shape->Width / 2;
                dirty->Y -= Shape->Height / 2;
            }
            surface->Copy_From(*dirty, *unknown_surface_839958, *dirty, false, true);
            unsigned level = (unsigned)unknown_40 < 3 ? unknown_40 : 3;
            CC_Draw_Shape(surface, Drawer, Shape, Frame, Point2D(X, Y), surface->Get_Rect(),
                          unknown_fade_flags_7e57f0[level] | Flags, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
            if (Anims != 0) {
                int index = Anims->ID(this);
                for (int i = 0; i < Anims->Count(); i++) {
                    if (i != index) {
                        (*Anims)[i]->Draw(surface, dirty);
                    }
                }
            }
            if ((unsigned)++unknown_40 >= 4) {
                CC_Draw_Shape(unknown_surface_839958, Drawer, Shape, Frame, Point2D(X, Y), surface->Get_Rect(),
                              Flags | 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
            }
            return !unknown_48;
        }
        return false;
    }
    dirty->Set(0, 0, 0, 0);
    return false;
}
