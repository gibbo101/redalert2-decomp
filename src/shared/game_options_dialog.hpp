// The GOptions dialog (GOptions.CPP; dialog 0xB6).
#ifndef RA2_SHARED_GAME_OPTIONS_DIALOG_HPP
#define RA2_SHARED_GAME_OPTIONS_DIALOG_HPP
#include "shared/win32_api.hpp"
// Shows dialog 0xB6, waits until a button stores the result in DWL_USER; returns it (0x004DDF20).
int Run_Game_Options_Dialog();
// The dialog procedure (0x004DDF90).
int __stdcall Game_Options_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
#endif
