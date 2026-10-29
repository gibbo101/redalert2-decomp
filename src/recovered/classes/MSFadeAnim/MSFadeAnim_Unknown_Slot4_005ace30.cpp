// bool MSFadeAnim::Unknown_Slot4(Surface *surface, Rect *dirty) (0x005ACE30, slot 4)
// Every unknown_24 ticks restores the old frame's area, redraws the other
// animations of Anims over it, steps the frame (true with an empty area when
// the last frame is passed and unknown_34 is clear) and the fade level, draws
// the new frame and reports the union of the old and new areas.
#include "shared/ms_anim.hpp"
// @ref _unknown_empty_rect=00a71808
// @ref ??0Rect@@QAE@HHHH@Z=0042bcd0

bool MSFadeAnim::Unknown_Slot4(Surface *surface, Rect *dirty)
{
    if (unknown_0C == true && Timer.Value() == 0) {
        Timer = CDTimerClass<SystemTimerClass>(unknown_24);
        int flags;
        if ((unsigned)unknown_40 < 4) {
            flags = unknown_fade_flags_7e57f0[unknown_40] | Flags;
        } else {
            flags = Flags | unknown_fade_flags_7e57f0[3];
        }
        Rect old = Frame_Rect();
        old.X = X + old.X;
        old.Y = Y + old.Y;
        if (flags & 0x200) {
            old.X -= Shape->Width / 2;
            old.Y -= Shape->Height / 2;
        }
        surface->Copy_From(old, *unknown_surface_839958, old, false, true);
        if (Anims != 0) {
            int index = Anims->ID(this);
            for (int i = 0; i < Anims->Count(); i++) {
                if (i != index) {
                    (*Anims)[i]->Draw(surface, &old);
                }
            }
        }
        if (++Frame > EndFrame) {
            if (!unknown_34) {
                dirty->Set(0, 0, 0, 0);
                return true;
            }
            Frame = StartFrame;
        }
        if ((unsigned)++unknown_40 < 4) {
            flags = unknown_fade_flags_7e57f0[unknown_40] | Flags;
        } else {
            flags = Flags | unknown_fade_flags_7e57f0[3];
        }
        CC_Draw_Shape(surface, Drawer, Shape, Frame, Point2D(X, Y), surface->Get_Rect(), flags, 0, 0, 0, 1000, 0, 0,
                      Point2D(0, 0));
        *dirty = Frame_Rect();
        dirty->X = X + dirty->X;
        dirty->Y = Y + dirty->Y;
        if (flags & 0x200) {
            dirty->X -= Shape->Width / 2;
            dirty->Y -= Shape->Height / 2;
        }
        *dirty = Union(*dirty, old);
        return false;
    }
    dirty->Set(0, 0, 0, 0);
    return false;
}
