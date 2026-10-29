// int __fastcall unknown_wrap_text_5ae9a0(WideString &text, MSFont *font, int width) (0x005AE9A0)
// Word wrap: each line ends at its last space, which becomes '\n'; a line
// without one is cut after a '-' or where it runs out of room (a '\n' is
// inserted). Returns the widest line.
#include "shared/ms_anim.hpp"
// @ref ??_C@_13DEJI@?$AA?6?$AA?$AA@=007e58ec

int __fastcall unknown_wrap_text_5ae9a0(WideString &text, MSFont *font, int width)
{
    int widest = 0;
    if (text == 0 || font == 0 || width <= font->Width) {
        return 0;
    }
    width -= font->Width;
    unsigned i = 0;
    while (text.Get_Char(i) != 0) {
        unsigned start = i;
        int line_width = 0;
        while (line_width < width && text.Get_Char(i) != 0 && text.Get_Char(i) != '\n' && text.Get_Char(i) != '@') {
            line_width += font->Char_Width(text.Get_Char(i++));
        }
        if (line_width >= width) {
            while (text.Get_Char(i) != 0 && text.Get_Char(i) != ' ' && text.Get_Char(i) != '\n') {
                if (i == start) {
                    break;
                }
                line_width -= font->Char_Width(text.Get_Char(--i));
            }
        }
        if (i == start) {
            while (line_width < width && text.Get_Char(i) != 0 && text.Get_Char(i) != ' ' && text.Get_Char(i) != '\n'
                   && text.Get_Char(i) != '@' && text.Get_Char(i) != '-') {
                line_width += font->Char_Width(text.Get_Char(i++));
            }
            if (line_width < width) {
                WideString first(text);
                first.Truncate(++i);
                WideString rest(text);
                rest.Remove(0, i);
                text = first + WideString(L"\n") + rest;
            } else {
                line_width -= font->Char_Width(text.Get_Char(i));
                WideString first(text);
                first.Truncate(i);
                WideString rest(text);
                rest.Remove(0, i);
                text = first + WideString(L"\n") + rest;
            }
        }
        if (line_width > widest) {
            widest = line_width;
        }
        if (text.Get_Char(i) != 0) {
            text.Set_Char('\n', i++);
        }
    }
    return widest;
}
