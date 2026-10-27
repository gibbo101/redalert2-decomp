// void ColorListClass::Remove_Item(int index) (0x0047D970, slot 42)
// Removes an entry and its colour.
#include "shared/color_list.hpp"
// @ref ?Remove_Item@ListClass@@UAEXH@Z=0053a0f0

void ColorListClass::Remove_Item(int index)
{
    if (index != -1) {
        Colors.Delete(index);
        ListClass::Remove_Item(index);
    }
}
