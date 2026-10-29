// bool MSPrintAnim::Unknown_Slot4(Surface *surface, Rect *dirty) (0x005AEDA0, slot 4)
// Types the next character once the per-character delay has run out: redraws
// the visible lines up to it (centring each line when Centered), scrolls to
// the next line when the text runs past the bottom of TextRect, and reports
// TextRect as the area to refresh. Once the text is finished it returns
// !unknown_48 after three more calls.
#include "shared/ms_anim.hpp"
#include "shared/msfont.hpp"
// @ref ?unknown_char_770400@WideString@@QBEGI@Z=00770400

bool MSPrintAnim::Unknown_Slot4(Surface *surface, Rect *dirty)
{
    dirty->X = 0;
    dirty->Y = 0;
    dirty->Width = 0;
    dirty->Height = 0;
    if (Timer.Value() != 0) {
        return false;
    }
    if (unknown_0C == true) {
        Timer = CDTimerClass<SystemTimerClass>(CharDelay);
        if (Position > Text.Length() && unknown_28 > 2) {
            return !unknown_48;
        }
        if (unknown_30 == true) {
            surface->Copy_From(TextRect, *unknown_surface_839958, TextRect, false, true);
        }
        int x = X;
        bool centered = Centered;
        int y = Y;
        for (unsigned index = LineStart; index <= Position; index++) {
            unsigned short ch = Text.unknown_char_770400(index);
            if (ch == 0) {
                unknown_28++;
                break;
            }
            if (centered) {
                WideString line(Text);
                line.Remove(0, index);
                int spacing = Font->Width;
                int width = Line_Width(line);
                int offset = (TextRect.Width - width - spacing) / 2;
                centered = false;
                x += offset;
                unknown_4C = offset;
            }
            if (ch == '\n') {
                x = X;
                centered = Centered;
                int height = Font->Height;
                y += height;
                if (height - Y + y > TextRect.Height) {
                    unsigned next = LineStart;
                    while (Text.Get_Char(next) != 0 && Text.Get_Char(next) != '\n') {
                        next++;
                    }
                    if (Text.Get_Char(next) == '\n') {
                        next++;
                    }
                    LineStart = next;
                    break;
                }
                continue;
            }
            unsigned style = (unknown_30 && Position - index < 2) ? Position - index : 2;
            Font->Print_Char(surface, ch, x, y, style, 1);
            x += Font->Char_Width(ch);
        }
        *dirty = TextRect;
        Position++;
    }
    return false;
}
