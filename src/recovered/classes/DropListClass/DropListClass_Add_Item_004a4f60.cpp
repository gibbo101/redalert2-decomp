// int DropListClass::Add_Item(wchar_t *text) (0x004A4F60, slot 39)
// Shows text in the field and appends it to the list.
#include "shared/gadget.hpp"
// @ref _wcsncpy=00783622

int DropListClass::Add_Item(wchar_t *text)
{
    wcsncpy(String, text, MaxLength);
    Flag_To_Redraw();
    return List.Add_Item(text);
}
