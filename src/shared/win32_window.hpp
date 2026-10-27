// Window and cursor coordinate declarations (HWND, RECT, POINT,
// GetClientRect, ClientToScreen) now live in shared/win32_api.hpp; this
// header holds the game's own window globals and small window helpers.
#ifndef RA2_SHARED_WIN32_WINDOW_HPP
#define RA2_SHARED_WIN32_WINDOW_HPP

#include "shared/win32_api.hpp"

extern HINSTANCE ProgramInstance;     // 0x00B26180 the module instance (dialog templates)
extern HWND MainWindow;               // 0x00B263D8 the game window (the one shared declaration)

// A window's screen rectangle made relative to the main window's client
// area; 0 (rect untouched) when GetWindowRect fails (0x00735690).
BOOL __fastcall Window_Rect_In_Main_Client(HWND window, RECT *rect);

// The client size of dialog template dialog_id: creates the dialog without a
// parent, reads its client rectangle and destroys it; size[0] = width,
// size[1] = height. The third argument is not read. Returns 1 (0x00735B50).
int __fastcall Dialog_Template_Size(int dialog_id, DLGPROC procedure, int unused, LONG *size);

#endif
