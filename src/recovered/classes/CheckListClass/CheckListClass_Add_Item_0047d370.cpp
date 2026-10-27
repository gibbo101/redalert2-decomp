// int CheckListClass::Add_Item(wchar_t *text) (0x0047D370, slot 34)
// Adds an unchecked entry.
#include "shared/check_list.hpp"
// @ref ?Add_Item@ListClass@@UAEHPAG@Z=0053a060
// @ref ??2@YAPAXI@Z=00782017

int CheckListClass::Add_Item(wchar_t *text)
{
    return ListClass::Add_Item((wchar_t *)new CheckObject(text, false));
}
