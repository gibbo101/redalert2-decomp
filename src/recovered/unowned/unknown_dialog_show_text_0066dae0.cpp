// void UnknownDialog_66dae0::Show_Text(int id) -- 0x0066DAE0
// Purpose: shows and enables control id of the dialog (window at +0x00),
// sends it (message 0x4B4) the trimmed part of the text at +0x08 after its
// first '-' (the empty string when there is none) and focuses it.
// Assumptions: the dialog owner and the message's meaning are unidentified
// (no direct callers); names are placeholders. The text buffer is used in
// place (strtrim, 0x006EEF10, trims it).
#include "shared/win32_api.hpp"
// @ref _strchr=00784130
// @ref ?strtrim@@YIPADPAD@Z=006eef10
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref __imp__ShowWindow@8=0079a498
// @ref __imp__EnableWindow@8=0079a490
// @ref __imp__SetFocus@4=0079a38c

WIN32_IMPORT BOOL WINAPI ShowWindow(HWND window, int command);
WIN32_IMPORT BOOL WINAPI EnableWindow(HWND window, BOOL enable);
WIN32_IMPORT HWND WINAPI SetFocus(HWND window);
extern "C" char *__cdecl strchr(char const *string, int character);
char *__fastcall strtrim(char *string);

class UnknownDialog_66dae0 {
public:
    void Show_Text(int id);

    HWND Window;                    // +0x00
    int unknown_04;
    char Text[1];                   // +0x08 (length unknown)
};

void UnknownDialog_66dae0::Show_Text(int id)
{
    HWND control = GetDlgItem(Window, id);
    if (control != 0) {
        ShowWindow(control, 5);
        EnableWindow(control, true);
        char *text = strchr(Text, '-');
        if (text != 0) {
            text++;
            strtrim(text);
        } else {
            text = "";
        }
        SendMessageA(control, 0x4B4, 0, (LPARAM)text);
        SetFocus(control);
    }
}
