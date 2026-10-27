// wchar_t *ListClass::Get_Item(int index) const (0x0053A480, slot 40)
#include "shared/gadget.hpp"

wchar_t *ListClass::Get_Item(int index) const
{
    if (List.Count() == 0) {
        return 0;
    }
    int last = List.Count() - 1;
    if (index >= last) {
        index = last;
    }
    return List[index];
}
