// int __stdcall Unknown_00513290(HWND, UINT, WPARAM, LPARAM) -- 0x00513290
#include "shared/win32_api.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/map_seed.hpp"

// A dialog procedure (pointer only): the common handler 0x005FFB00 first; WM_PAINT sends 0x4F0
// to item 0x71A; the init message enables item 0x689 only when a saved game exists; WM_COMMAND
// ids 0x688, 0x689, 0x68A, 0x579 and 0x686 store 8, 9, 0xA, 0xB and 0x12 in the int the window's
// long 8 points at.
int __stdcall Unknown_00513290(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
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
        switch ((unsigned short)wparam) {
        case 0x688:
            *choice = 8;
            return 0;
        case 0x689:
            *choice = 9;
            return 0;
        case 0x68A:
            *choice = 0xA;
            return 0;
        case 0x579:
            *choice = 0xB;
            return 0;
        case 0x686:
            *choice = 0x12;
            return 0;
        }
        break;
    case 0x497:
        {
            HWND item = GetDlgItem(window, 0x689);
            if (item) {
                bool saved = LoadOptionsClass().Has_Saved_Games_0053c5c0();
                EnableWindow(item, saved);
            }
        }
        break;
    }
    return 0;
}
