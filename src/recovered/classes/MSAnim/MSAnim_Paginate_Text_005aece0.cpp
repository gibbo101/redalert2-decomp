// int __fastcall unknown_paginate_text_5aece0(WideString &text, MSFont *font, int height) (0x005AECE0)
// Counts the pages of already wrapped text: a running total of line heights that reaches height starts a new
// page, marked with a form feed (0x0C) in the text. As in the original, the position only advances past a line's
// end when that end is not '\n' (name and meaning are hypotheses).
#include "shared/ms_anim.hpp"

int __fastcall unknown_paginate_text_5aece0(WideString &text, MSFont *font, int height)
{
    if (text == 0 || font == 0 || height < font->Height) {
        return 0;
    }
    unsigned i = 0;
    int pages = 0;
    int y = 0;
    while (text.Get_Char(i) != 0) {
        while (text.Get_Char(i) != 0 && text.Get_Char(i) != '\n') {
            i++;
        }
        if (text.Get_Char(i) != '\n') {
            y += font->Height;
            if (y >= height) {
                y = 0;
                pages++;
                text.Set_Char(0x0C, i);
            }
            i++;
        }
    }
    return pages;
}
