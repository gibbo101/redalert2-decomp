// BitFontClass *Font_For_Style(int style) (0x00497A50)
// The current bit font; the style is not consulted (one font).
#include "shared/text_print.hpp"

BitFontClass *__fastcall Font_For_Style(int style)
{
    return BitFont;
}
