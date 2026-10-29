// bool MSPrintAnim::Unknown_5af210(Surface *surface, Rect *dirty) (0x005AF210)
// Slot 4's line-at-a-time variant (no caller, not in the vtable): every
// CharDelay ticks draws the line from LineStart at unknown_50 in fade step
// unknown_24 (0..2, stepping while unknown_30) and reports its area; after the
// last step moves to the next line with a "bleep1". True once the text is done.
#include "shared/ms_anim.hpp"
#include "shared/audio.hpp"
// @ref ??_C@_06KMLL@bleep1?$AA@=007e58f0
// @ref __real@4@40058000000000000000=007a6e78

bool MSPrintAnim::Unknown_5af210(Surface *surface, Rect *dirty)
{
    if (Timer.Value() == 0 && unknown_0C == true) {
        Timer = CDTimerClass<SystemTimerClass>(CharDelay);
        if (LineStart >= Text.Length()) {
            Audio_Event_Play_Named("bleep1", unknown_volume_a40b44 * 64.0f);
            return true;
        }
        if (unknown_30 == true && unknown_54.Is_Valid()) {
            surface->Copy_From(unknown_54, *unknown_surface_839958, unknown_54, false, true);
        }
        int x = X;
        if (Centered) {
            x += unknown_4C;
        }
        unsigned index = LineStart;
        unsigned short ch = Text.Get_Char(index++);
        while (ch != '\n' && ch != 0) {
            Font->Print_Char(surface, ch, x, unknown_50, Position, 0);
            x += Font->Char_Width(ch);
            ch = Text.Get_Char(index++);
        }
        dirty->Set(TextRect.X, unknown_50, TextRect.Width, Font->Height);
        if (Position == 2) {
            unknown_54.Set(0, 0, 0, 0);
            LineStart = index;
            if (ch == '\n') {
                Audio_Event_Play_Named("bleep1", unknown_volume_a40b44 * 64.0f);
                unknown_50 += Font->Height;
            }
        } else {
            unknown_54 = *dirty;
        }
        if (unknown_30 == true) {
            if (++Position > 2) {
                Position = 0;
            }
        }
        return false;
    }
    dirty->Set(0, 0, 0, 0);
    return false;
}
