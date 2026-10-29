// void MSPrintAnim::Draw(Surface *surface, Rect const *clip) (0x005AF030, slot 5)
// Draws the typed characters from LineStart on (unless TextRect lies outside
// clip), stopping at the bottom of the surface.
// The inline ::Intersect (rect_intersect.hpp, visible from MSBinkAnim::Draw on)
// stays out of line here (0x0041FDF0) because the Line_Width site later in the
// body is still pending when the nested site is decided (depth-first rule,
// docs/VC6_MATCHING_NOTES.md).
#include "shared/ms_anim.hpp"
#include "shared/msfont.hpp"

void MSPrintAnim::Draw(Surface *surface, Rect const *clip)
{
    if (clip != 0) {
        Rect area = clip->Intersect(TextRect);
        if (!area.Is_Valid()) {
            return;
        }
    }
    int x = X;
    bool centered = Centered;
    int y = Y;
    unsigned end = (Position < Text.Length()) ? Position : Text.Length();
    for (unsigned index = LineStart; index < end; index++) {
        if (Text.Get_Char(index) == '\n') {
            x = X;
            centered = Centered;
            int height = Font->Height;
            y += height;
            if (height + y >= surface->Get_Height()) {
                return;
            }
        } else {
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
            Font->Print_Char(surface, Text.Get_Char(index), x, y, 2, 1);
            x += Font->Char_Width(Text.Get_Char(index));
        }
    }
}
