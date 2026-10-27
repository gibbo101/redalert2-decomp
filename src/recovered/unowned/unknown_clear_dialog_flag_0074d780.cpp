// void __fastcall unknown_clear_dialog_flag_74d780(unsigned mask) -- 0x0074D780
// Purpose: when the window 0xC4 exists (0x00735940), clears mask from the
// flags at 0x00B2ABE0 and, once none remain, passes the window to
// 0x007357E0 with 0; then focuses control 0x540 of the current dialog
// (0x00735B10).
// Assumptions: the dialog helpers (0x007357E0, 0x00735940, 0x00735B10) and
// the flags are unidentified; names are placeholders.
#include "shared/win32_api.hpp"
// @ref ?Unknown_00735940@@YIPAXH@Z=00735940
// @ref ?Unknown_007357E0@@YIXPAXH@Z=007357e0
// @ref ?Unknown_00735B10@@YAPAUHWND__@@XZ=00735b10
// @ref ?unknown_dialog_flags_b2abe0@@3IA=00b2abe0
// @ref __imp__SetFocus@4=0079a38c

WIN32_IMPORT HWND WINAPI SetFocus(HWND window);
void *__fastcall Unknown_00735940(int id);
void __fastcall Unknown_007357E0(void *window, int arg2);
HWND Unknown_00735B10();
extern unsigned unknown_dialog_flags_b2abe0;

void __fastcall unknown_clear_dialog_flag_74d780(unsigned mask)
{
    void *window = Unknown_00735940(0xC4);
    if (window != 0) {
        unknown_dialog_flags_b2abe0 &= ~mask;
        if (unknown_dialog_flags_b2abe0 == 0) {
            Unknown_007357E0(window, 0);
        }
    }
    HWND dialog = Unknown_00735B10();
    HWND control = GetDlgItem(dialog, 0x540);
    if (control != 0) {
        SetFocus(control);
    }
}
