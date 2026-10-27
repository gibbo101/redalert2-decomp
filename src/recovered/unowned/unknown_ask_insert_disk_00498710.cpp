// bool __stdcall unknown_ask_insert_disk(int disk) -- 0x00498710
// Purpose: asks the player with an OK/Cancel message box ("Hey!",
// "Please insert disk %d") to insert a disk; true when OK was chosen.
// No direct callers. Owner unit not identified (CD handling).
#include "shared/win32_api.hpp"
// @ref _sprintf=007820f4
// @ref __imp__MessageBoxA@16=0079a47c
// @ref ??_C@_04ONPB@Hey?$CB?$AA@=007d5c70
// @ref ??_C@_0BG@CDHG@Please?5insert?5disk?5?$CFd?$AA@=007d5c78

extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);
WIN32_IMPORT int __stdcall MessageBoxA(HWND window, char const *text, char const *caption, unsigned int type);

bool __stdcall unknown_ask_insert_disk_00498710(int disk)
{
    char text[256];
    sprintf(text, "Please insert disk %d", disk);
    return MessageBoxA(0, text, "Hey!", 1) == 1 ? true : false;    // MB_OKCANCEL, IDOK
}
