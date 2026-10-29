// The GOptions.CPP dialogs: the leave-game choice (dialog 0xB6) and the in-game options menu.
#ifndef RA2_SHARED_GAME_OPTIONS_DIALOG_HPP
#define RA2_SHARED_GAME_OPTIONS_DIALOG_HPP
#include "shared/win32_api.hpp"
// Shows dialog 0xB6, waits until a button stores the result in DWL_USER; returns it (0x004DDF20).
int Run_Game_Options_Dialog();
// The dialog procedure (0x004DDF90).
int __stdcall Game_Options_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
// The in-game options menu (dialog 0xB5 in single-player games, 0xBBA/0xFF otherwise; shown by
// Unknown_004DD7D0): its dialog procedure (0x004DD8A0) and its setup (0x004DDE00).
int __stdcall Options_Menu_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
void __fastcall Options_Menu_Init(HWND window);
#endif
