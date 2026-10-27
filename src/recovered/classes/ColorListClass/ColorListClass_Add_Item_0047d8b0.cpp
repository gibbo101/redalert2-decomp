// int ColorListClass::Add_Item(wchar_t *text, int color) (0x0047D8B0, slot 51)
// Adds an entry drawn in a colour scheme.
#include "shared/color_list.hpp"
// @ref ?Add_Item@ListClass@@UAEHPAG@Z=0053a060

int ColorListClass::Add_Item(wchar_t *text, int color)
{
    Colors.Add(color);
    return ListClass::Add_Item(text);
}
