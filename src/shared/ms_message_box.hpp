// The main-screen message box (unit 0x005B4690-0x005B49DF, between MSFont.cpp
// and the next `_$E` at 0x005B49E0; its file name is not evidenced).
//
// Message_Box shows dialog template 0xCE/0x120/0x121 (one, two or three
// buttons) with a wide-string text and up to three button captions, runs
// the message loop until a button sets the result, and returns it (button
// 0x5AE: 0, IDOK/IDCANCEL: 1, 0x5AF: 2). The dialog procedure finds the
// result through DWL_USER (index 8). Names of the functions and of every
// unknown_ helper are hypotheses.
#ifndef RA2_SHARED_MS_MESSAGE_BOX_HPP
#define RA2_SHARED_MS_MESSAGE_BOX_HPP

#include "shared/unknown_globals.hpp"
#include "shared/mouse.hpp"
#include "shared/rect.hpp"
#include "shared/shape_file.hpp"
#include "shared/wwmouse.hpp"
#include "shared/win32_api.hpp"
#include "shared/ww_message_box.hpp"

typedef int (WINAPI *DialogProc)(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

int __stdcall Message_Box_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);           // 0x005B48C0
void __fastcall Message_Box_Command(HWND window, int id, HWND control, unsigned code);                             // 0x005B4980


void __fastcall unknown_5159b0(int unknown1, bool unknown2);                         // 0x005159B0
HWND __fastcall unknown_create_dialog_5ff610(int resource, DialogProc proc, int unknown3);  // 0x005FF610
// A modeless dialog with the text and one cancel button; the button sets *cancelled (0x006001E0).
HWND __fastcall unknown_cancel_dialog_6001e0(unsigned short const *text, unsigned short const *button, bool *cancelled);
// Sends 0x4B2 with value to the dialog's control 0x5B0 (its text) and repaints the dialog (0x006002C0).
void __fastcall unknown_set_dialog_item_5b0(HWND dialog, LPARAM value);
void __fastcall unknown_dialog_5ff7c0(HWND window);                                  // 0x005FF7C0 (after setup)
void __fastcall unknown_dialog_5ff6e0(HWND window);                                  // 0x005FF6E0 (when done)
int __fastcall unknown_dialog_proc_5ffb00(HWND window, UINT message, WPARAM wparam, LPARAM lparam);  // 0x005FFB00
bool unknown_6000d0();                                                               // 0x006000D0 ends the wait when true
void __fastcall unknown_517370(bool unknown1);                                       // 0x00517370 idle step
bool __fastcall unknown_moving_736d80(HWND window, WPARAM wparam, LPARAM lparam);    // 0x00736D80 WM_MOVING

#endif
