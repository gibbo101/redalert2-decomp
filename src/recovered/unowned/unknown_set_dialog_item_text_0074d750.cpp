// void __fastcall unknown_set_dialog_item_text(LPARAM text) -- 0x0074D750
// Purpose: sends message 0x4B2 with `text` to control 0x5B2 of dialog 0xC4
// (0x00735940 finds the dialog) when that dialog exists.
// Assumptions: what control 0x5B2 and message 0x4B2 are is unknown.
#include "shared/win32_api.hpp"
// @ref ?Unknown_00735940@@YIPAXH@Z=00735940
// @ref __imp__SendDlgItemMessageA@20=0079a484

void *__fastcall Unknown_00735940(int id);              // 0x00735940 (a dialog by id)
WIN32_IMPORT LRESULT WINAPI SendDlgItemMessageA(HWND dialog, int item, UINT message, WPARAM wparam, LPARAM lparam);

void __fastcall unknown_set_dialog_item_text(LPARAM text)
{
    HWND dialog = (HWND)Unknown_00735940(0xC4);
    if (dialog != 0) {
        SendDlgItemMessageA(dialog, 0x5B2, 0x4B2, 0, text);
    }
}
