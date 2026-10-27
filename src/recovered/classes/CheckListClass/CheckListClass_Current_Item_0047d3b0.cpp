// wchar_t *CheckListClass::Current_Item() const (0x0047D3B0, slot 39)
#include "shared/check_list.hpp"
// @ref ?Current_Item@ListClass@@UBEPAGXZ=0053a4a0

wchar_t *CheckListClass::Current_Item() const
{
    CheckObject *object = (CheckObject *)ListClass::Current_Item();
    if (object != 0) {
        return object->Text;
    }
    return 0;
}
