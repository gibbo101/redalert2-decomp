// void __fastcall Create_Main_Window(HINSTANCE instance, int command_show, int width, int height) (0x00737BD0)
// Registers the "Red Alert 2" window class and creates the game window: a captionless popup the size
// of the client area in windowed mode, a topmost screen-sized one otherwise; then the IME context.
#include "shared/win_stub.hpp"
#include "shared/dsurface.hpp"

// @ref __imp__InitCommonControls@0=0079a02c
// @ref _ImmGetContext@4=00781c20
// @ref ?Windows_Procedure@@YGJPAUHWND__@@IIJ@Z=007375a0
// @ref ?unknown_icon_b263d4@@3PAXA=00b263d4
// @ref ?unknown_cursor_b263d0@@3PAXA=00b263d0
// @ref ?unknown_command_show_b263cc@@3HA=00b263cc
// @ref ?IMEContext@@3PAUHIMC__@@A=00b263e4
// @ref ??_C@_0M@ECB@Red?5Alert?52?$AA@=007f4f84

void __fastcall Create_Main_Window(HINSTANCE instance, int command_show, int width, int height)
{
    WNDCLASSA wndclass;
    RECT rect;

    InitCommonControls();
    unknown_icon_b263d4 = LoadIconA(instance, MAKEINTRESOURCEA(0x5D));
    unknown_cursor_b263d0 = LoadCursorA(ProgramInstance, MAKEINTRESOURCEA(0x68));
    wndclass.style = 3;
    wndclass.lpfnWndProc = Windows_Procedure;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = instance;
    wndclass.hIcon = unknown_icon_b263d4;
    wndclass.hCursor = unknown_cursor_b263d0;
    wndclass.hbrBackground = 0;
    wndclass.lpszMenuName = 0;
    wndclass.lpszClassName = "Red Alert 2";
    RegisterClassA(&wndclass);
    if (unknown_flag_851cb0) {
        MainWindow = CreateWindowExA(0, "Red Alert 2", "Red Alert 2", 0x2CA0000, 0, 0, 0, 0, 0, 0, instance, 0);
        SetRect(&rect, 0, 0, width, height);
        AdjustWindowRectEx(&rect, GetWindowLongA(MainWindow, -16), GetMenu(MainWindow) != 0,
                           GetWindowLongA(MainWindow, -20));
        MoveWindow(MainWindow, 0, 0, rect.right - rect.left, rect.bottom - rect.top, TRUE);
    } else {
        MainWindow = CreateWindowExA(8, "Red Alert 2", "Red Alert 2", 0x82000000, 0, 0, GetSystemMetrics(0),
                                     GetSystemMetrics(1), 0, 0, instance, 0);
    }
    IMEContext = ImmGetContext(MainWindow);
    ShowWindow(MainWindow, 1);
    unknown_command_show_b263cc = command_show;
    UpdateWindow(MainWindow);
    SetFocus(MainWindow);
    RegisterHotKey(MainWindow, 1, 7, 0x4D);
    SetCursor(LoadCursorA(ProgramInstance, MAKEINTRESOURCEA(0x68)));
}
