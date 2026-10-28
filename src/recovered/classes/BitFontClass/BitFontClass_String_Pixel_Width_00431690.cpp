// int BitFontClass::String_Pixel_Width(wchar_t const *string, int arg2) const (0x00431690)
// The width Get_Text_Area measures for the string.
#include "shared/text_print.hpp"
// @ref ?Get_Text_Area@BitFontClass@@QAE_NPBGPAH1H@Z=004314b0

int BitFontClass::String_Pixel_Width(wchar_t const *string, int arg2) const
{
    ((BitFontClass *)this)->Get_Text_Area(string, &arg2, 0, arg2);
    return arg2;
}
