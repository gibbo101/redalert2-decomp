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

// The stack of open modeless dialogs: 0x005FF610 pushes each dialog it creates with its
// template resource id, 0x005FF6E0 removes it and makes the new top the current dialog
// (0x00735910-0x007359B0 search it). Its capacity is not evidenced.
struct DialogStackEntry {
    HWND Window;                    // +0x00
    int Resource;                   // +0x04
};
extern DialogStackEntry DialogStack[];   // 0x00B25BB8
extern HWND CurrentDialog;               // 0x00B25DD4 the top of the stack (0 when empty)
extern int CurrentDialogResource;        // 0x00B25DD8 its resource id
extern int DialogStackCount;             // 0x00B25DE0

struct DLGTEMPLATE;
WIN32_IMPORT HWND WINAPI CreateDialogIndirectParamA(HINSTANCE instance, DLGTEMPLATE const *dialog, HWND parent,
                                                    DLGPROC procedure, LPARAM parameter);

// The locked data of resource id of the given type in the module at 0x00851CA8 (0x004954E0).
void *__fastcall Load_Resource_004954e0(unsigned int id, char const *type);

#endif
