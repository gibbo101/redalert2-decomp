// bool CheckListClass::Is_Checked(int index) const (0x0047D4E0)
#include "shared/check_list.hpp"
// @ref ?Get_Item@ListClass@@UBEPAGH@Z=0053a480

bool CheckListClass::Is_Checked(int index) const
{
    CheckObject *object = (CheckObject *)ListClass::Get_Item(index);
    if (object != 0) {
        return object->IsChecked;
    }
    return false;
}
