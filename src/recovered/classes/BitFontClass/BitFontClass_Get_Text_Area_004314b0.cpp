// bool BitFontClass::Get_Text_Area(wchar_t const *text, int *width, int *height, int max_width) (0x004314B0)
// Measures the text: the widest line and the total height, wrapping at the
// last space (or mid-word) when a line passes max_width (0: no limit). Tabs
// advance to the next tab stop; CR, LF and CR LF end a line.
#include "shared/text_print.hpp"

bool BitFontClass::Get_Text_Area(wchar_t const *text, int *width, int *height, int max_width)
{
    int space_widest = 0;
    if (!Data || !text) {
        if (height) {
            *height = 0;
        }
        if (width) {
            *width = 0;
        }
        return false;
    }

    int widest = 0;
    int line_height = Height;
    int total = Height;
    int x = 0;
    int count = 0;
    wchar_t const *space = 0;
    wchar_t last = 0;
    wchar_t c = *text++;
    while (c) {
        switch (c) {
            case '\n':
            case '\r':
                if (last != '\r') {
                    x = 0;
                    count = 0;
                    total += line_height;
                }
                break;

            case '\t':
                x += unknown_28;
                x -= x % unknown_28;
                break;

            case ' ':
                space = text;
                space_widest = widest;
                // fall through
            default: {
                unsigned char *glyph = Glyph_Data(c);
                if (!glyph) {
                    glyph = (unsigned char *)unknown_08;
                }
                if (glyph) {
                    count++;
                    x += unknown_2c + *glyph;
                    if (max_width && x > max_width) {
                        if (space) {
                            if (count > 1) {
                                text = space;
                                widest = space_widest;
                            }
                        } else {
                            if (count > 1) {
                                x -= unknown_2c + *glyph;
                                text--;
                            }
                            if (x > widest) {
                                widest = x;
                            }
                        }
                        x = 0;
                        count = 0;
                        total += line_height;
                        space = 0;
                    } else if (x > widest) {
                        widest = x;
                    }
                }
                break;
            }
        }
        last = c;
        c = *text++;
    }
    if (width) {
        *width = widest;
    }
    if (height) {
        *height = total;
    }
    return true;
}
