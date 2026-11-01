// int __fastcall unknown_combo_find_data_736e10(HWND combo, int start, int data) (0x00736E10)
#include "shared/win_util.hpp"

int __fastcall unknown_combo_find_data_736e10(HWND combo, int start, int data)
{
    int count = SendMessageA(combo, 0x146, 0, 0);    // CB_GETCOUNT
    for (int index = start; index < count; index++) {
        if (SendMessageA(combo, 0x150, index, 0) == data) {   // CB_GETITEMDATA
            return index;
        }
    }
    return -1;
}
