// Wstring __fastcall Unknown_00757cc0(HWND list) (0x00757CC0)
// The first list entry from the selection on whose text starts with '(' and holds a ')': that text between
// the parentheses; unknown_wstring_b29cd4 when there is none.
#include "shared/wol_sink.hpp"

Wstring __fastcall Unknown_00757cc0(HWND list)
{
    int index = SendMessageA(list, 0x188, 0, 0);
    if (index == -1) index = 0;
    while (index < SendMessageA(list, 0x18B, 0, 0)) {
        WideString text;
        unknown_get_list_item_wide_text(list, index, text);
        if (text.Get_Char(0) == '(' && text.Truncate_At(')')) {
            text.Remove_Character('(');
            return Narrow_Copy_00771280(text);
        }
        index++;
    }
    return unknown_wstring_b29cd4;
}
