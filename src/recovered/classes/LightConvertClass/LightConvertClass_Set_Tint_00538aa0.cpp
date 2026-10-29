// LightConvertClass::Set_Tint(int, int, int, bool) (0x00538AA0, vtable slot 1)
// Clamps the tint to 0..2000 (1000 = neutral), records it as the current or stored colour, then fills one
// 256-entry pixel table per shadow level: the remapped colours scale by the tint, the others by the level
// brightness, both rising from black to double over the levels.  The four table builders (0x0079777A..)
// are selected by the pixel format code 0x007DF868; any other format builds the table inline.
#include "shared/light_convert.hpp"
#include "shared/hicolor.hpp"
// @ref ?Set_Tint@LightConvertClass@@QAEXHHH_N@Z=00538aa0
// @ref __real@8@3ffb8637bd05af6c6800=007a55e8
extern "C" unsigned char DAT_007df768[];
extern "C" int DAT_007df868;
void __cdecl FUN_0079777a(PaletteClass const *palette, unsigned short *table, int red, int green, int blue, int level, unsigned char const *remap);
void __cdecl FUN_00797aba(PaletteClass const *palette, unsigned short *table, int red, int green, int blue, int level, unsigned char const *remap);
void __cdecl FUN_00797440(PaletteClass const *palette, unsigned short *table, int red, int green, int blue, int level, unsigned char const *remap);
void __cdecl FUN_00797dfa(PaletteClass const *palette, unsigned short *table, int red, int green, int blue, int level, unsigned char const *remap);

void LightConvertClass::Set_Tint(int red, int green, int blue, bool stored)
{
    if (unknown_shadow_count >= 1) {
        if (unknown_190 == 0) {
            unknown_190 = DAT_007df768;
        }
        if (red != -1) {
            red = (red < 2000) ? red : 2000;
            red = (red > 0) ? red : 0;
            green = (green < 2000) ? green : 2000;
            green = (green > 0) ? green : 0;
            blue = (blue < 2000) ? blue : 2000;
            blue = (blue > 0) ? blue : 0;
        }
        if (stored) {
            if (red == -1) {
                red = StoredRed;
                blue = StoredBlue;
                green = StoredGreen;
            } else {
                StoredRed = red;
                StoredGreen = green;
                StoredBlue = blue;
            }
            unknown_1b0 = true;
        } else {
            if (red == -1) {
                red = Red;
                green = Green;
                blue = Blue;
            } else {
                Red = red;
                Green = green;
                Blue = blue;
            }
            unknown_1b0 = false;
        }
        int red_step = (int)(red * 1000 * 0.065536);
        int green_step = (int)(green * 1000 * 0.065536);
        int blue_step = (int)(blue * 1000 * 0.065536);
        int last = unknown_shadow_count - 1;
        unsigned short *table = (unsigned short *)AlphaPalette;
        int limit = unknown_shadow_count * 30 / 200 - 1;
        limit = (limit > 0) ? limit : 0;
        if (limit >= (last >> 1)) {
            limit = last >> 1;
        }
        for (int i = 0; i <= unknown_shadow_count - 1; i++) {
            int r;
            int g;
            int b;
            int level;
            if (unknown_shadow_count > 1) {
                r = red_step * 2 * i / last;
                g = green_step * 2 * i / last;
                b = blue_step * 2 * i / last;
                if (i > limit) {
                    level = 0x10000;
                } else {
                    level = i * 0x10000 / limit;
                }
            } else {
                r = red_step;
                g = green_step;
                b = blue_step;
                level = 0x10000;
            }
            switch (DAT_007df868) {
            case 0:
                FUN_0079777a(ArtPalette, table, r, g, b, level, unknown_190);
                table += 256;
                break;
            case 1:
                FUN_00797aba(ArtPalette, table, r, g, b, level, unknown_190);
                table += 256;
                break;
            case 2:
                FUN_00797440(ArtPalette, table, r, g, b, level, unknown_190);
                table += 256;
                break;
            case 3:
                FUN_00797dfa(ArtPalette, table, r, g, b, level, unknown_190);
                table += 256;
                break;
            default:
                *table++ = 0;
                for (int c = 1; c < 256; c++) {
                    int pr;
                    int pg;
                    int pb;
                    if (unknown_190[c] != 0) {
                        pr = (*ArtPalette)[c].Red * r >> 16;
                        pg = (*ArtPalette)[c].Green * g >> 16;
                        pb = (*ArtPalette)[c].Blue * b >> 16;
                    } else {
                        pr = (*ArtPalette)[c].Red * level >> 16;
                        pg = (*ArtPalette)[c].Green * level >> 16;
                        pb = (*ArtPalette)[c].Blue * level >> 16;
                    }
                    if (pr >= 255) pr = 255;
                    if (pg >= 255) pg = 255;
                    if (pb >= 255) pb = 255;
                    *table++ = (unsigned short)Build_Hicolor_Pixel(pr, pg, pb);
                }
                break;
            }
        }
    }
}
