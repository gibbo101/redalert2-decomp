// wchar_t *CheckListClass::Get_Item(int index) const (0x0047D3C0, slot 40)
#include "shared/check_list.hpp"
// @ref ?Get_Item@ListClass@@UBEPAGH@Z=0053a480

wchar_t *CheckListClass::Get_Item(int index) const
{
    CheckObject *object = (CheckObject *)ListClass::Get_Item(index);
    if (object != 0) {
        return object->Text;
    }
    return 0;
}
