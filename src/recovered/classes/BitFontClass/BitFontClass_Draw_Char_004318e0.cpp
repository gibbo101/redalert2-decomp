// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// int BitFontClass::Draw_Char(wchar_t character, int x, int y, int color_arg) (0x004318E0): draws one
// character at x, y on the locked surface (a tab moves to the next tab stop from unknown_20); color -1: the
// font colour; a character without a glyph uses Missing_Glyph. Clipped to ClipBox when Clipping is set.
// The x after the character. From ra2-decomp BitFont::Blit (YR 0x00434120), adapted to our names.
#include "shared/text_print.hpp"
#include "shared/win32_api.hpp"

#define BLIT_CLIPPED(mask) \
    if (cx >= clipL && cx <= clipR && (bits & (mask))) *d = color; \
    d++; cx++; w--;

#define BLIT_PLAIN(mask) \
    if (bits & (mask)) *d = color; \
    d++; w--;

int BitFontClass::Draw_Char(wchar_t character, int x, int y, int color_arg)
{
    if (character == 9) {
        x += unknown_28;
        return x - (x - unknown_20) % unknown_28;
    }
    unsigned short color = Color;
    if (color_arg != -1) color = color_arg;
    unsigned char *glyph = Glyph_Data(character);
    if (!glyph) {
        glyph = (unsigned char *)Missing_Glyph(&color);
        if (!glyph) return x;
    }
    if (!Buffer) return x;
    unsigned char *data = glyph + 1;
    int width = *glyph;
    int height = Data->unknown_08;
    if (Clipping) {
        tagRECT rect;
        tagRECT clipped;
        SetRect((RECT *)&rect, x, y, x + width - 1, y + height - 1);
        if (!Intersect_Rect(&clipped, &rect, &ClipBox)) return unknown_2c + width + x;
        if (rect.left < clipped.left || rect.right > clipped.right || rect.top < clipped.top || rect.bottom > clipped.bottom) {
            int skip = clipped.top - rect.top;
            int rows = clipped.bottom - clipped.top + 1;
            y += skip;
            data += Width * skip;
            short *line = (short *)Buffer + (Pitch * y + x);
            int clipL = clipped.left;
            int clipR = clipped.right;
            while (rows--) {
                int w = width;
                int cx = x;
                short *d = line;
                unsigned char *p = data;
                do {
                    unsigned char bits = *p++;
                    if (bits == 0) {
                        d += 8;
                        w -= 8;
                        cx += 8;
                        continue;
                    }
                    BLIT_CLIPPED(0x80) if (w <= 0) break;
                    BLIT_CLIPPED(0x40) if (w <= 0) break;
                    BLIT_CLIPPED(0x20) if (w <= 0) break;
                    BLIT_CLIPPED(0x10) if (w <= 0) break;
                    BLIT_CLIPPED(8) if (w <= 0) break;
                    BLIT_CLIPPED(4) if (w <= 0) break;
                    BLIT_CLIPPED(2) if (w <= 0) break;
                    BLIT_CLIPPED(1)
                } while (w > 0);
                data += Width;
                line += Pitch;
                y++;
            }
            return unknown_2c + width + x;
        }
    }
    short *line = (short *)Buffer + (Pitch * y + x);
    while (height--) {
        int w = width;
        unsigned char *p = data;
        short *d = line;
        do {
            unsigned char bits = *p++;
            if (bits == 0) {
                d += 8;
                w -= 8;
                continue;
            }
            BLIT_PLAIN(0x80) if (w <= 0) break;
            BLIT_PLAIN(0x40) if (w <= 0) break;
            BLIT_PLAIN(0x20) if (w <= 0) break;
            BLIT_PLAIN(0x10) if (w <= 0) break;
            BLIT_PLAIN(8) if (w <= 0) break;
            BLIT_PLAIN(4) if (w <= 0) break;
            BLIT_PLAIN(2) if (w <= 0) break;
            BLIT_PLAIN(1)
        } while (w > 0);
        data += Width;
        line += Pitch;
    }
    return unknown_2c + width + x;
}
