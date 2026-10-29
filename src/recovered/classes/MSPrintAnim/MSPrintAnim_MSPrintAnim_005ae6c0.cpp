// MSPrintAnim::MSPrintAnim(WideString const &text, int x, int y, MSFont *font, Rect const &rect,
//     unsigned position, int char_delay, bool unknown_30, bool centered) (0x005AE6C0)
// Fits TextRect to the text in rect and, when centred, works out the first
// line's centring offset.
#include "shared/ms_anim.hpp"
// @ref ??_7MSPrintAnim@@6B@=007a6e54
// @ref ??_7MSAnim@@6B@=007a6d3c
// @ref ??0WideString@@QAE@ABV0@@Z=0076fa10
// @ref ?Set_Rect@MSPrintAnim@@QAEXABVRect@@@Z=005ae7e0

MSPrintAnim::MSPrintAnim(WideString const &text, int x, int y, MSFont *font, Rect const &rect, unsigned position,
                         int char_delay, bool unknown_30, bool centered) :
    MSAnim(x, y),
    Text(text),
    LineStart(0),
    Position(position),
    unknown_28(0),
    CharDelay(char_delay),
    unknown_30(unknown_30),
    Font(font),
    unknown_48(false),
    Centered(centered),
    unknown_4C(0)
{
    Timer = CDTimerClass<SystemTimerClass>(position);
    Set_Rect(rect);
    if (centered) {
        int spacing = Font->Width;
        int width = Line_Width(Text);
        unknown_4C = (TextRect.Width - width - spacing) / 2;
    }
}
