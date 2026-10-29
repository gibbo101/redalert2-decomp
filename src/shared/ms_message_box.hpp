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
#include "shared/dialog_create.hpp"


int __stdcall Message_Box_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);           // 0x005B48C0
void __fastcall Message_Box_Command(HWND window, int id, HWND control, unsigned code);                             // 0x005B4980


// The WM_INITDIALOG lparam of a dialog that 0x005FF610 creates: the resource id and its third
// argument (the WDT faction dialog proc 0x007689C0 keeps Param as its DWL_USER value).
struct UnknownDialogCreateParam {
    unsigned short Resource;    // +0x00
    int Param;                  // +0x04
};
// A modeless dialog with the text and one cancel button; the button sets *cancelled (0x006001E0).
HWND __fastcall unknown_cancel_dialog_6001e0(unsigned short const *text, unsigned short const *button, bool *cancelled);
// Shows the yes/no dialog 0x10D with the text and waits for a choice; true for button 0x5C1 (0x00600C80).
bool __fastcall unknown_choice_dialog_600c80(unsigned short const *text);
// Its dialog procedure: the common handler 0x005FFB00 first, then the button sets *cancelled and queues Escape (0x00600260).
int __stdcall unknown_cancel_dialog_proc_600260(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
// Sends 0x4B2 with value to the dialog's control 0x5B0 (its text) and repaints the dialog (0x006002C0).
void __fastcall unknown_set_dialog_item_5b0(HWND dialog, LPARAM value);
// Moves a window to x, y relative to the main window's client origin (-1 keeps that coordinate),
// keeping its size and without repainting (0x00600120).
void __fastcall unknown_move_window_600120(HWND window, int x, int y);
void __fastcall unknown_dialog_5ff7c0(HWND window);                                  // 0x005FF7C0 (after setup)
void __fastcall unknown_dialog_5ff6e0(HWND window);                                  // 0x005FF6E0 (when done)
int __fastcall unknown_dialog_proc_5ffb00(HWND window, UINT message, WPARAM wparam, LPARAM lparam);  // 0x005FFB00
// A dialog procedure: the common handler first, then WM_COMMAND from controls 0x5C0-0x5C1 stores the id in *DWL_USER (0x00600D50).
int __stdcall unknown_choice_dialog_proc_600d50(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
void __fastcall unknown_5115f0(HWND dialog);                                       // 0x005115F0 (0x005EAB60 with its flag)
void __fastcall unknown_517370(bool unknown1);                                       // 0x00517370 idle step
bool __fastcall unknown_moving_736d80(HWND window, WPARAM wparam, LPARAM lparam);    // 0x00736D80 WM_MOVING

#endif
