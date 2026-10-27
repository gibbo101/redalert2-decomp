// wchar_t *ListClass::Current_Item() const (0x0053A4A0, slot 39)
#include "shared/gadget.hpp"

wchar_t *ListClass::Current_Item() const
{
    if (List.Count() <= SelectedIndex) {
        return 0;
    }
    return List[SelectedIndex];
}
