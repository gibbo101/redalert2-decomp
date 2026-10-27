// void CheckListClass::Set_Selected_Index(wchar_t *text) (0x0047D450, slot 45)
// Selects the first entry with this text.
#include "shared/check_list.hpp"
// @ref ?Get_Item@ListClass@@UBEPAGH@Z=0053a480
// @ref __wcsicmp=00796318

void CheckListClass::Set_Selected_Index(wchar_t *text)
{
    for (int index = 0; index < Count(); index++) {
        CheckObject *object = (CheckObject *)ListClass::Get_Item(index);
        if (object != 0 && _wcsicmp(object->Text, text) == 0) {
            Set_Selected_Index(index);
            return;
        }
    }
}
