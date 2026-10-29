// void __fastcall Add_Chat_Dot_005c3040() (0x005C3040)
// Appends "." to the last line of the chat list 0x53F of the current dialog (or the nearest dialog below it
// that has one), starting a new line once a line has 0x24 characters; redraw is off meanwhile (0x49D).
#include "shared/lobby.hpp"
// @ref ??_C@_13DOBH@?$AA?4?$AA?$AA@=007e6e58

void __fastcall Add_Chat_Dot_005c3040()
{
    if (Unknown_00735B10() != 0) {
        HWND window = Unknown_00735B10();
        HWND list = GetDlgItem(window, 0x53f);
        while (list == 0) {
            window = (HWND)unknown_previous_key((int)window);
            if (window == 0) {
                return;
            }
            list = GetDlgItem(window, 0x53f);
        }
        LRESULT redraw = SendMessageA(list, 0x49d, 0, 1);
        int count = SendMessageA(list, 0x18b, 0, 0);                    // LB_GETCOUNT
        WideString text;
        if (count > 0) {
            unknown_get_list_item_wide_text(list, count - 1, text);
        }
        if (text.Length() < 0x24) {
            SendMessageA(list, 0x182, count - 1, 0);                    // LB_DELETESTRING
            text += L".";
        } else {
            text = L".";
            count++;
        }
        SendMessageA(list, 0x4cd, 0, (LPARAM)text.unknown_text_770430());
        while (count > 500) {
            SendMessageA(list, 0x182, 0, 0);
        }
        SendMessageA(list, 0x49d, 0, redraw);
    }
}
