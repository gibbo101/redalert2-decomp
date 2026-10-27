// void CheckListClass::Check_Item(int index, bool checked) (0x0047D4B0)
// Sets an entry's check mark, redrawing on a change.
#include "shared/check_list.hpp"
// @ref ?Get_Item@ListClass@@UBEPAGH@Z=0053a480

void CheckListClass::Check_Item(int index, bool checked)
{
    CheckObject *object = (CheckObject *)ListClass::Get_Item(index);
    if (object != 0 && object->IsChecked != checked) {
        object->IsChecked = checked;
        Flag_To_Redraw();
    }
}
