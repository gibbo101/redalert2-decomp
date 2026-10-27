// void __fastcall unknown_send_byte_message(HWND window, unsigned char value) -- 0x005E1FB0
// Purpose: sends the custom message 0x4E5 (WM_USER + 0xE5) with a byte value
// as lparam. No direct callers.
#include "shared/win32_api.hpp"
// @ref __imp__SendMessageA@16=0079a4a0

WIN32_IMPORT long __stdcall SendMessageA(HWND window, unsigned int message, unsigned int wparam, long lparam);

void __fastcall unknown_send_byte_message_005e1fb0(HWND window, unsigned char value)
{
    SendMessageA(window, 0x4e5, 0, value);
}
