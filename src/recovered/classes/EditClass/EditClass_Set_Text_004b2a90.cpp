// void EditClass::Set_Text(wchar_t *text, int max_len) (0x004B2A90, slot 34)
#include "shared/gadget.hpp"

void EditClass::Set_Text(wchar_t *text, int max_len)
{
    String = text;
    MaxLength = max_len - 1;
    Length = wcslen(String);
    Flag_To_Redraw();
}
