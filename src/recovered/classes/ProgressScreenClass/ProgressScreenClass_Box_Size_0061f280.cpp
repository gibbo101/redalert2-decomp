// void ProgressScreenClass::Box_Size(int *width, int *height, int rows, bool flag) (0x0061F280)
// The size of the progress box: shape, flag and name side by side plus
// margins, one row per player.
#include "shared/progress_screen.hpp"
// @ref ??_C@_01FJFF@W?$AA@=007db208
// @ref ?Font_For_Style@@YIPAVBitFontClass@@H@Z=00497a50
// @ref ?Unknown_006FA180@@YIPAGPBD@Z=006fa180
// @ref ?String_Pixel_Width@BitFontClass@@QBEHPBGH@Z=00431690

void ProgressScreenClass::Box_Size(int *width, int *height, int rows, bool flag)
{
    int shape_width = 0, shape_height = 0;
    Shape_Size(&shape_width, &shape_height);
    int flag_width = 0, flag_height = 0;
    if (flag) {
        Flag_Size(&flag_width, &flag_height);
    }
    int text_width = 0, text_height = 0;
    Text_Size(&text_width, &text_height);
    *width = text_width + flag_width + shape_width + 20;
    *height = shape_height > flag_height ? shape_height : flag_height;
    *height = *height > text_height ? *height : text_height;
    *width += 10;
    *height += 4;
    if (rows > 1) {
        *height *= rows;
    }
}
