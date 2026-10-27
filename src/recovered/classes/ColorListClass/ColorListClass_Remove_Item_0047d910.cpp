// void ColorListClass::Remove_Item(wchar_t *text) (0x0047D910, slot 43)
// Removes the entry with this text and its colour.
#include "shared/color_list.hpp"
// @ref ?Remove_Item@ListClass@@UAEXPAG@Z=0053a1c0

void ColorListClass::Remove_Item(wchar_t *text)
{
    int index = List.ID(text);
    if (index != -1) {
        Colors.Delete(index);
        ListClass::Remove_Item(text);
    }
}
