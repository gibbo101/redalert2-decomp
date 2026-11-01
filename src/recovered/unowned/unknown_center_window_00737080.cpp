// void __fastcall unknown_center_window_737080(HWND window, HWND parent) (0x00737080)
#include "shared/win_util.hpp"
#include "shared/win32_window.hpp"
#include "shared/unknown_globals.hpp"

void __fastcall unknown_center_window_737080(HWND window, HWND parent)
{
    RECT parent_rect;
    GetClientRect(parent, &parent_rect);
    if (parent == MainWindow) {
        parent_rect.right = unknown_8523e0;
        parent_rect.bottom = unknown_8523e4;
    }
    ClientToScreen(parent, (POINT *)&parent_rect.left);
    ClientToScreen(parent, (POINT *)&parent_rect.right);
    parent_rect.right -= parent_rect.left;
    parent_rect.bottom -= parent_rect.top;

    RECT rect;
    GetClientRect(window, &rect);
    ClientToScreen(window, (POINT *)&rect.left);
    ClientToScreen(window, (POINT *)&rect.right);
    rect.right -= rect.left;
    rect.bottom -= rect.top;

    int x = (parent_rect.right - rect.right + 1) / 2;
    int y = (parent_rect.bottom - rect.bottom + 1) / 2;
    if (x < 0) {
        x = 0;
    }
    if (y < 0) {
        y = 0;
    }
    SetWindowPos(window, 0, x, y, -1, -1, 5);   // SWP_NOSIZE | SWP_NOZORDER
}
