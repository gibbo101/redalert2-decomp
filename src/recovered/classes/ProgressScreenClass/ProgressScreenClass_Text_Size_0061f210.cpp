// void __fastcall ProgressScreenClass::Text_Size(int *width, int *height) (0x0061F210)
// The size of a name of fifteen "W"s in font style 0x46.
#include "shared/progress_screen.hpp"
#include "shared/text_print.hpp"
#include "shared/ipx_manager.hpp"
// @ref ??_C@_01FJFF@W?$AA@=007db208

void __fastcall ProgressScreenClass::Text_Size(int *width, int *height)
{
    BitFontClass *font = Font_For_Style(0x46);
    wchar_t text[16];
    for (int index = 0; index < 15; index++) {
        text[index] = *Unknown_006FA180("W");
    }
    text[15] = 0;
    *width = font->String_Pixel_Width(text, 0);
    *height = font->Height;
}
