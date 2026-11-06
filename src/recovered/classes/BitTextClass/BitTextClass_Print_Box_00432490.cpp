// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// bool BitTextClass::Print_Box(...) (0x00432490): word-wrapped text in a box of width x height (0: unbounded);
// flags 1 centres, 2 right-aligns each line; with limit, at most limit characters are drawn and the last fade
// of them fade toward unknown_rgb_ab6849. False without a font or text.
// From ra2-decomp BitText::DrawText (YR 0x00434CD0), adapted to our names.
// @ref ?unknown_rgb_ab6849@@3VRGBClass@@A=00ab6849
#include "shared/text_print.hpp"
#include "shared/hicolor_pixel.hpp"
#include "shared/rgb_globals.hpp"

// A hicolor pixel as its three channels.
inline RGBClass Int_To_RGB(int color)
{
    return RGBClass(
        (unsigned char)((unsigned short)color >> unknown_shift_852fb8) << unknown_shift_852fbc,
        (unsigned char)((unsigned short)color >> unknown_shift_852fc8) << unknown_shift_852fcc,
        (unsigned char)((unsigned short)color >> unknown_shift_852fc0) << unknown_shift_852fc4);
}

// Three channels as a hicolor pixel.
inline int RGB_To_Int(RGBClass const &rgb)
{
    return RGB_To_Pixel(rgb.Get_Red(), rgb.Get_Green(), rgb.Get_Blue());
}

// The offset of a line linewidth wide in width: flags 1 centres it, 2 right-aligns it.
inline int Align_Offset(int width, int linewidth, int flags)
{
    int offset = 0;
    if (width > linewidth) {
        if (flags & 1) {
            offset = (width - linewidth) / 2;
        } else if (flags & 2) {
            offset = width - linewidth;
        }
    }
    return offset;
}

// The glyph of a character, or of '?' when the font has none.
inline unsigned char *Char_Bitmap(BitFontClass *font, wchar_t ch)
{
    unsigned char *glyph = font->Glyph_Data(ch);
    if (!glyph) {
        glyph = font->Glyph_Data('?');
    }
    return glyph;
}

// Draws start..end as one line; false when the character limit is reached.
inline bool Draw_Line(BitFontClass *font, wchar_t const *&start, wchar_t const *end, int x, int y, int width, int linewidth, int flags, int &drawn, int &px, int color, int limit, int fade)
{
    px = x + Align_Offset(width, linewidth, flags);
    while (start < end) {
        drawn++;
        int c = color;
        if (limit) {
            if (drawn >= limit) {
                c = -1;
            } else {
                int left = limit - drawn - 1;
                if (left < fade) {
                    RGBClass rgb = Int_To_RGB(color);
                    rgb.Adjust((255 / fade) * (fade - left), unknown_rgb_ab6849);
                    c = RGB_To_Int(rgb);
                }
            }
        }
        if (c == -1) {
            return false;
        }
        px = font->Draw_Char(*start++, px, y, c);
    }
    return true;
}

bool BitTextClass::Print_Box(BitFontClass *font, Surface *surface, wchar_t const *text, int x, int y, int width,
                             int height, int flags, int limit, int fade)
{
    int linewidth = 0;
    if (!font || !text) {
        return false;
    }

    font->Set_Surface(surface);
    font->Set_unknown_20(x);

    wchar_t const *start = text;
    int liney = 0;
    int spacewidth = 0;
    wchar_t const *space = 0;
    wchar_t prev = 0;
    int chars = 0;
    int color = font->Color;
    int drawn = 0;
    int px;
    wchar_t ch = *text;

    while (ch) {
        switch (ch) {
        case '\r':
        case '\n':
            if (prev != '\r') {
                if (!Draw_Line(font, start, text, x, y, width, linewidth, flags, drawn, px, color, limit, fade)) {
                    font->Release_Surface(surface);
                    return true;
                }
                linewidth = 0;
                chars = 0;
                liney += font->Height;
                if (height && liney >= height) {
                    font->Release_Surface(surface);
                    return true;
                }
                y += font->Height;
            }
            start++;
            break;

        case '\t':
            linewidth += font->unknown_28;
            linewidth -= linewidth % font->unknown_28;
            break;

        case ' ':
            spacewidth = linewidth;
            space = text;

        default:
            {
                unsigned char *glyph = Char_Bitmap(font, ch);
                if (!glyph) {
                    break;
                }
                chars++;
                int w = *glyph + font->unknown_2c;
                linewidth += w;
                if (width && linewidth > width) {
                    if (space) {
                        if (chars > 1) {
                            linewidth = spacewidth;
                            text = space;
                        }
                    } else if (chars > 1) {
                        linewidth -= w;
                        text--;
                    }
                    px = x + Align_Offset(width, linewidth, flags);
                    while (start < text) {
                        drawn++;
                        int c = color;
                        if (limit) {
                            if (drawn >= limit) {
                                c = -1;
                            } else {
                                int left = limit - drawn - 1;
                                if (left < fade) {
                                    RGBClass rgb = Int_To_RGB(color);
                                    rgb.Adjust((255 / fade) * (fade - left), unknown_rgb_ab6849);
                                    c = RGB_To_Int(rgb);
                                }
                            }
                        }
                        if (c == -1) {
                            font->Release_Surface(surface);
                            return true;
                        }
                        px = font->Draw_Char(*start++, px, y, c);
                    }
                    if (text == space) {
                        space = 0;
                        start++;
                    }
                    linewidth = 0;
                    chars = 0;
                    liney += font->Height;
                    if (height && liney >= height) {
                        font->Release_Surface(surface);
                        return true;
                    }
                    y += font->Height;
                }
            }
            break;
        }
        prev = ch;
        text++;
        ch = *text;
    }

    px = x + Align_Offset(width, linewidth, flags);
    while (start < text) {
        drawn++;
        int c = color;
        if (limit) {
            if (drawn >= limit) {
                c = -1;
            } else {
                int left = limit - drawn - 1;
                if (left < fade) {
                    RGBClass rgb = Int_To_RGB(color);
                    rgb.Adjust((255 / fade) * (fade - left), unknown_rgb_ab6849);
                    c = RGB_To_Int(rgb);
                }
            }
        }
        if (c == -1) {
            font->Release_Surface(surface);
            return true;
        }
        px = font->Draw_Char(*start++, px, y, c);
    }
    font->Release_Surface(surface);
    return true;
}
