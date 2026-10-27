// void __fastcall unknown_set_dialog_wide_text(HWND dialog, UnknownTextOwner_005c3450 *owner) -- 0x005C3450
// Purpose: sends the owner's wide text (+0x20; 0x00770430 returns the
// buffer or an empty string) to dialog control 0x6EC with the custom message
// 0x4B2 (WM_USER + 0xB2). No direct callers; bound by linear sweep to the
// ret (the frozen inventory bound stops at the SendMessageA call).
#include "shared/win32_api.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ?unknown_text_770430@UnknownWideText_005c3450@@QBEPBGXZ=00770430

WIN32_IMPORT HWND __stdcall GetDlgItem(HWND dialog, int id);
WIN32_IMPORT long __stdcall SendMessageA(HWND window, unsigned int message, unsigned int wparam, long lparam);

// A wide string holder (0x007703F0 area); 0x00770430 returns its buffer or
// the shared empty string 0x00839D4C.
class UnknownWideText_005c3450 {
public:
    unsigned short const *unknown_text_770430() const;
    unsigned short *Buffer;
};

struct UnknownTextOwner_005c3450 {
    char unknown_00[0x20];
    UnknownWideText_005c3450 unknown_text_20;
};

void __fastcall unknown_set_dialog_wide_text_005c3450(HWND dialog, UnknownTextOwner_005c3450 *owner)
{
    HWND item = GetDlgItem(dialog, 0x6ec);
    SendMessageA(item, 0x4b2, 0, (long)owner->unknown_text_20.unknown_text_770430());
}
