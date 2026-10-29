// void __fastcall Unknown_00626FA0(HWND list) (0x00626FA0): trims a list box to 50 lines and shows the last.
#include "shared/queue.hpp"

void __fastcall Unknown_00626FA0(HWND list)
{
    int count = SendMessageA(list, 0x018B, 0, 0);           // LB_GETCOUNT
    if (count > 50) {
        SendMessageA(list, 0x0182, 0, 0);    // LB_DELETESTRING
        count--;
    }
    SendMessageA(list, 0x0197, count - 1, 0);       // LB_SETTOPINDEX
}
