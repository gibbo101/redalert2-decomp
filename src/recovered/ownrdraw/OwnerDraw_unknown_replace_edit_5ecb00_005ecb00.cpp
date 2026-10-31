// @ref __imp__GetWindowLongA@8=0079a48c
// @ref __imp__SetWindowLongA@12=0079a488
// @ref __imp__GetClassNameA@12=0079a4e0
// @ref __imp__GetParent@4=0079a500
// @ref __imp__EnableWindow@8=0079a490
// @ref __imp__ShowWindow@8=0079a498
// @ref ?ProgramInstance@@3PAXA=00b26180
// @ref ??_C@_04EDLP@Edit?$AA@=007e8df0
// @ref ??_C@_07FHL@NewEdit?$AA@=007e8de8
// @ref ??_C@_07NOMM@ListBox?$AA@=007e8de0
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/crt_string.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// EnumChildWindows callback: clears each control's user data and replaces a visible, enabled edit control with
// an owner list box of the same place and size (user data: "NewEdit" and the edit's style), swapping their IDs.
// (GWL_USERDATA -21, GWL_ID -12, WS_VISIBLE 0x10000000, WS_DISABLED 0x08000000; the list box style is
// WS_CHILD | LBS_HASSTRINGS | LBS_NOTIFY, plus WS_TABSTOP from the edit.)
BOOL __stdcall unknown_replace_edit_5ecb00(HWND window, LPARAM)
{
    unsigned int style = GetWindowLongA(window, GWL_STYLE);
    SetWindowLongA(window, -21, 0);
    if ((style & 0x10000000) && !(style & 0x08000000)) {
        char name[128];
        GetClassNameA(window, name, sizeof(name));
        if (strcmp(name, "Edit") == 0) {
            HWND parent = GetParent(window);
            RECT rect;
            RECT parent_rect;
            Window_Rect_In_Main_Client(window, &rect);
            Window_Rect_In_Main_Client(parent, &parent_rect);
            int x = rect.left - parent_rect.left;
            int y = rect.top - parent_rect.top;
            DWORD list_style = 0x40000110;
            if (style & 0x10000) {
                list_style = 0x40010110;
            }
            HWND list = CreateWindowExA(0, "ListBox", 0, list_style, x, y,
                                        rect.right - rect.left, rect.bottom - rect.top, parent, 0, ProgramInstance, 0);
            LONG *data = (LONG *)operator new(8);
            data[0] = (LONG)"NewEdit";
            data[1] = GetWindowLongA(window, GWL_STYLE);
            SetWindowLongA(list, -21, (LONG)data);
            EnableWindow(window, FALSE);
            ShowWindow(window, SW_HIDE);
            EnableWindow(list, TRUE);
            ShowWindow(list, SW_SHOWNORMAL);
            LONG id = GetWindowLongA(window, -12);
            SetWindowLongA(window, -12, GetWindowLongA(list, -12));
            SetWindowLongA(list, -12, id);
        }
    }
    return TRUE;
}

}
