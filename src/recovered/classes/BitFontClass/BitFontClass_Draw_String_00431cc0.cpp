// BitFontClass::Draw_String (0x00431CC0): draws the text from x (CR and LF skipped; at most count
// characters, 0: all); with fade, the first fade characters fade toward unknown_rgb_ab6849 and the
// text stops after them (the result is then the full text's end). The next x.
#include "shared/text_print.hpp"
#include "shared/hicolor.hpp"
#include "shared/rgb_globals.hpp"
#include "shared/hicolor_pixel.hpp"
// @ref ?unknown_rgb_ab6849@@3VRGBClass@@A=00ab6849

int BitFontClass::Draw_String(wchar_t const *text, int x, int y, int count, int fade)
{
    int index = 0;
    wchar_t character = *text++;
    unsigned short color = Color;
    if (character != 0) {
        int step = fade - 1;
        int ratio = (9 - fade) * 31;
        while (character != 0) {
            if (fade != 0) {
                if (index >= fade) {
                    Color = color;
                    int width;
                    Get_Text_Area(text, &width, 0, 0);
                    return width + x;
                }
                if (step < 8) {
                    RGBClass rgb = Pixel_To_RGB(color);
                    rgb.Adjust(ratio, unknown_rgb_ab6849);
                    Color = (unsigned short)(((rgb.Red >> unknown_shift_852fbc) << unknown_shift_852fb8)
                                           | ((rgb.Blue >> unknown_shift_852fc4) << unknown_shift_852fc0)
                                           | ((rgb.Green >> unknown_shift_852fcc) << unknown_shift_852fc8));
                }
                index++;
                ratio += 31;
                step--;
            }
            if (character != 13 && character != 10) {
                x = Draw_Char(character, x, y, -1);
            }
            if (count != 0 && --count == 0) {
                break;
            }
            character = *text++;
        }
    }
    Color = color;
    return x;
}
