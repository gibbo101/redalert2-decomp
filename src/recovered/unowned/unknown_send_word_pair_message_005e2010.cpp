// void __fastcall unknown_send_word_pair_message(HWND window, int low, int high) -- 0x005E2010
// Purpose: sends the custom message 0x4E8 (WM_USER + 0xE8) with two 16-bit
// values packed into lparam (MAKELONG(low, high)). No direct callers.
#include "shared/win32_api.hpp"
// @ref __imp__SendMessageA@16=0079a4a0

WIN32_IMPORT long __stdcall SendMessageA(HWND window, unsigned int message, unsigned int wparam, long lparam);

void __fastcall unknown_send_word_pair_message_005e2010(HWND window, int low, int high)
{
    SendMessageA(window, 0x4e8, 0, (long)((unsigned short)low | ((unsigned long)(unsigned short)high << 16)));
}
