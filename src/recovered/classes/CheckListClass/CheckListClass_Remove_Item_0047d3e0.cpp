// void CheckListClass::Remove_Item(wchar_t *text) (0x0047D3E0, slot 43)
// Removes (and deletes) the first entry with this text.
#include "shared/check_list.hpp"
// @ref ?Get_Item@ListClass@@UBEPAGH@Z=0053a480
// @ref ?Remove_Item@ListClass@@UAEXH@Z=0053a0f0
// @ref __wcsicmp=00796318
// @ref ??3@YAXPAX@Z=00781d3b

void CheckListClass::Remove_Item(wchar_t *text)
{
    for (int index = 0; index < Count(); index++) {
        CheckObject *object = (CheckObject *)ListClass::Get_Item(index);
        if (object != 0 && _wcsicmp(object->Text, text) == 0) {
            ListClass::Remove_Item(index);
            delete object;
            return;
        }
    }
}
