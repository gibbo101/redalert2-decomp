// BOOL __fastcall Window_Rect_In_Main_Client(HWND window, RECT *rect) -- 0x00735690
// Purpose: GetWindowRect of window, then offsets it by the screen position
// of MainWindow's client origin, giving the rectangle in main-window client
// coordinates. Returns GetWindowRect's result.
#include "shared/win32_window.hpp"
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8

BOOL __fastcall Window_Rect_In_Main_Client(HWND window, RECT *rect)
{
    BOOL result;
    RECT client;

    result = GetWindowRect(window, rect);
    if (result == 0) {
        return 0;
    }
    GetClientRect(MainWindow, &client);
    ClientToScreen(MainWindow, (POINT *)&client);
    rect->left = rect->left - client.left;
    rect->right = rect->right - client.left;
    rect->top = rect->top - client.top;
    rect->bottom = rect->bottom - client.top;
    return result;
}
