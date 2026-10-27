// CheckListClass::CheckListClass(int id, int x, int y, int w, int h, unsigned flags, void const *up, void const *down) (0x0047D2E0)
// A list that accepts input.
#include "shared/check_list.hpp"
// @ref ??0ListClass@@QAE@HHHHHIPBX0@Z=00539bf0
// @ref ??_7CheckListClass@@6B@=0079db9c

CheckListClass::CheckListClass(int id, int x, int y, int w, int h, unsigned flags, void const *up, void const *down) :
    ListClass(id, x, y, w, h, flags, up, down),
    IsReadOnly(false)
{
}
