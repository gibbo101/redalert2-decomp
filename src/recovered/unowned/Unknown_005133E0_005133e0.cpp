// int __stdcall Unknown_005133E0(HWND, UINT, WPARAM, LPARAM) -- 0x005133E0
// Body 0x005133E0-0x005134B5: code to 0x00513495, then the WM_COMMAND jump table (5 dwords at
// 0x00513498) and its byte index table (10 bytes at 0x005134AC).
#include "shared/win32_api.hpp"
#include "shared/ms_message_box.hpp"

// A dialog procedure (pointer only): the common handler 0x005FFB00 first; WM_PAINT sends 0x4F0
// to item 0x71A; WM_COMMAND ids 0x68D, 0x68E, 0x68F and 0x686 store 0xD, 0xE, 0xF and 0x12 in
// the int the window's long 8 points at.
int __stdcall Unknown_005133E0(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result != 0) {
        return result;
    }
    int *choice = (int *)GetWindowLongA(window, 8);
    switch (message) {
    case 0xF:
        {
            HWND item = GetDlgItem(window, 0x71A);
            SendMessageA(item, 0x4F0, 0, 0);
        }
        break;
    case 0x111:
        switch (wparam & 0xFFFF) {
        case 0x68D:
            *choice = 0xD;
            return 0;
        case 0x68E:
            *choice = 0xE;
            return 0;
        case 0x68F:
            *choice = 0xF;
            return 0;
        case 0x686:
            *choice = 0x12;
            return 0;
        }
        break;
    }
    return 0;
}
