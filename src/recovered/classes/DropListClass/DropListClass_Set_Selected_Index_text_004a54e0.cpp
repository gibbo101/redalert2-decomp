// void DropListClass::Set_Selected_Index(wchar_t *text) (0x004A54E0, slot 42)
// Selects the first list item equal to text (case-insensitive).
#include "shared/gadget.hpp"
// @ref __wcsicmp=00796318

void DropListClass::Set_Selected_Index(wchar_t *text)
{
    if (text != 0) {
        for (int index = 0; index < Count(); index++) {
            if (_wcsicmp(text, List.Get_Item(index)) == 0) {
                Set_Selected_Index(index);
                break;
            }
        }
    }
}
