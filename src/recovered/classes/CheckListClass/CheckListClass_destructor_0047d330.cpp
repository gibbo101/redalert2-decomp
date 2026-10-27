// CheckListClass::~CheckListClass() (0x0047D330)
// Deletes the check objects while removing the entries.
#include "shared/check_list.hpp"
// @ref ?Get_Item@ListClass@@UBEPAGH@Z=0053a480
// @ref ?Remove_Item@ListClass@@UAEXH@Z=0053a0f0
// @ref ??1ListClass@@UAE@XZ=00539fc0
// @ref ??3@YAXPAX@Z=00781d3b

CheckListClass::~CheckListClass()
{
    while (List.Count()) {
        CheckObject *object = (CheckObject *)ListClass::Get_Item(0);
        ListClass::Remove_Item(0);
        delete object;
    }
}
