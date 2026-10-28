// int ProgressScreenClass::Row_Y(int y, int row, bool flag) (0x0061F3B0)
// The top of a row: y plus row times the height of a one-row box.
#include "shared/progress_screen.hpp"
// @ref ??_C@_01FJFF@W?$AA@=007db208
// @ref ?Font_For_Style@@YIPAVBitFontClass@@H@Z=00497a50
// @ref ?Unknown_006FA180@@YIPAGPBD@Z=006fa180
// @ref ?String_Pixel_Width@BitFontClass@@QBEHPBGH@Z=00431690

int ProgressScreenClass::Row_Y(int y, int row, bool flag)
{
    int width = 0, height = 0;
    Box_Size(&width, &height, 1, flag);
    return y + height * row;
}
