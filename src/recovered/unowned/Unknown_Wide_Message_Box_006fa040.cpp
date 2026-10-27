// void __fastcall Unknown_006FA040(HWND window, unsigned short const *text, unsigned short const *caption, unsigned int type) (0x006FA040)
// Shows a message box for wide strings: both are narrowed with
// WideCharToMultiByte (text into 0x1400 bytes, caption into 0x800) and
// MessageBoxA shows them. The stack frame is probed first (0x00783850).
#include "shared/win32_api.hpp"
// @ref __imp__WideCharToMultiByte@32=0079a23c
// @ref __imp__MessageBoxA@16=0079a47c

WIN32_IMPORT int __stdcall WideCharToMultiByte(unsigned int codepage, unsigned long flags, unsigned short const *wide, int wide_length,
                                              char *narrow, int narrow_length, char const *default_char, int *used_default);
WIN32_IMPORT int __stdcall MessageBoxA(HWND window, char const *text, char const *caption, unsigned int type);

void __fastcall Unknown_006FA040(HWND window, unsigned short const *text, unsigned short const *caption, unsigned int type)
{
    char narrow_caption[0x800];
    char narrow_text[0x1400];
    WideCharToMultiByte(0, 0, text, -1, narrow_text, 0x1400, 0, 0);
    WideCharToMultiByte(0, 0, caption, -1, narrow_caption, 0x800, 0, 0);
    MessageBoxA(window, narrow_text, narrow_caption, type);
}
