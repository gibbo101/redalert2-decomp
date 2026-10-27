// void ListClass::Remove_Item(wchar_t *text) (0x0053A1C0, slot 43)
#include "shared/gadget.hpp"

void ListClass::Remove_Item(wchar_t *text)
{
    if (text != 0) {
        Remove_Item(List.ID(text));
    }
}
