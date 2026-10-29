// @ref ?unknown_8523e0@@3HA=008523e0
// @ref ?unknown_8523e4@@3HA=008523e4
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
#include "shared/unknown_globals.hpp"
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/ms_message_box.hpp"

void __fastcall unknown_move_window_600120(HWND window, int x, int y)
{
    RECT screen;
    RECT rect;
    screen.right = unknown_8523e0;
    screen.left = 0;
    screen.top = 0;
    screen.bottom = unknown_8523e4;
    ClientToScreen(MainWindow, (POINT *)&screen.left);
    ClientToScreen(MainWindow, (POINT *)&screen.right);
    GetWindowRect(window, &rect);
    rect.right -= rect.left;
    rect.bottom -= rect.top;
    rect.left = x == -1 ? rect.left - screen.left : x;
    rect.top = y == -1 ? rect.top - screen.top : y;
    MoveWindow(window, rect.left, rect.top, rect.right, rect.bottom, FALSE);
}
