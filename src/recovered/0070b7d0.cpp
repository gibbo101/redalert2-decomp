// void Hicolor_Clear_Table() -- 0x0070B7D0
// Releases the pixel table.
#include "shared/unvq_table.hpp"

void Hicolor_Clear_Table()
{
    if (HicolorTable != 0) {
        delete [] HicolorTable;
        HicolorTable = 0;
    }
}

static bool Hicolor_Set_Mode(int mode)
{
    bool valid = false;
    int red_shift;
    int green_shift;
    int blue_shift;

    switch (mode) {
        case HICOLOR_MODE_555:
            red_shift = 10;
            green_shift = 5;
            blue_shift = 0;
            valid = true;
            break;
        case HICOLOR_MODE_655:
            red_shift = 11;
            green_shift = 5;
            blue_shift = 0;
            valid = true;
            break;
        case HICOLOR_MODE_565:
            red_shift = 11;
            green_shift = 6;
            blue_shift = 0;
            valid = true;
            break;
        case HICOLOR_MODE_556:
            red_shift = 11;
            green_shift = 6;
            blue_shift = 1;
            valid = true;
            break;
        default:
            break;
    }

    if (valid) {
        for (int red = 0; red < 32; red++) {
            for (int green = 0; green < 32; green++) {
                for (int blue = 0; blue < 32; blue++) {
                    HicolorTable[(unsigned short)(((red << 5) | green) << 5) | (unsigned short)blue] =
                        (unsigned short)((red << red_shift) | (green << green_shift) | (blue << blue_shift));
                }
            }
        }
        return true;
    }
    return false;
}
