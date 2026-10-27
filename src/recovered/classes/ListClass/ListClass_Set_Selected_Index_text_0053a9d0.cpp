// void ListClass::Set_Selected_Index(wchar_t *text) (0x0053A9D0, slot 45)
// Selects the first item equal to text (case-insensitive).
#include "shared/gadget.hpp"
// @ref __wcsicmp=00796318

void ListClass::Set_Selected_Index(wchar_t *text)
{
    if (text != 0 && List.Count() > 0) {
        for (int index = 0; index < List.Count(); index++) {
            if (_wcsicmp(List[index], text) == 0) {
                Set_Selected_Index(index);
                break;
            }
        }
    }
}
