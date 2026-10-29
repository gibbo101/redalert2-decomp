// void __fastcall Add_List_Text_005c2f20(HWND list, wchar_t const *text, int length, int color) (0x005C2F20)
#include "shared/lobby.hpp"
// @ref ?unknown_list_text_a71ea8@@3PAGA=00a71ea8

void __fastcall Add_List_Text_005c2f20(HWND list, wchar_t const *text, int length, int color)
{
    memset(unknown_list_text_a71ea8, 0, sizeof(unknown_list_text_a71ea8));
    wcsncpy(unknown_list_text_a71ea8, text, length);
    wchar_t *end = wcschr(unknown_list_text_a71ea8, '\r');
    if (end == 0) {
        end = wcschr(unknown_list_text_a71ea8, '\n');
    }
    if (end != 0) {
        *end = 0;
    }
    LRESULT redraw = SendMessageA(list, 0x49d, 0, 1);
    int top = SendMessageA(list, 0x18e, 0, 0);                  // LB_GETTOPINDEX
    int count = SendMessageA(list, 0x18b, 0, 0);                // LB_GETCOUNT
    int height = SendMessageA(list, 0x1a1, top, 0);             // LB_GETITEMHEIGHT
    RECT rect;
    GetWindowRect(list, &rect);
    bool at_bottom = count - top <= (rect.bottom - rect.top) / height;
    if (count > 500) {
        SendMessageA(list, 0x182, 0, 0);                        // LB_DELETESTRING
        count--;
    }
    int index = SendMessageA(list, 0x4cd, 0, (LPARAM)unknown_list_text_a71ea8);
    if (color != -1) {
        SendMessageA(list, 0x498, index, color);
    }
    if (at_bottom) {
        SendMessageA(list, 0x197, count, 0);                    // LB_SETTOPINDEX
    }
    SendMessageA(list, 0x49d, 0, redraw);
}
