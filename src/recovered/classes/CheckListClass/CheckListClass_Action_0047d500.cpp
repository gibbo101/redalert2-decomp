// int CheckListClass::Action(unsigned flags, unsigned &key) (0x0047D500, slot 31)
// Ignored while read-only; a left press toggles the selected entry's mark.
#include "shared/check_list.hpp"
// @ref ?Action@ListClass@@UAEHIAAI@Z=0053a1f0
// @ref ?Get_Item@ListClass@@UBEPAGH@Z=0053a480

int CheckListClass::Action(unsigned flags, unsigned &key)
{
    if (IsReadOnly) {
        return 0;
    }
    int result = ListClass::Action(flags, key);
    if (flags & 1) {
        Check_Item(SelectedIndex, !Is_Checked(SelectedIndex));
    }
    return result;
}
