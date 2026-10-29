// Dialog creation (0x005FF610), split out of shared/ms_message_box.hpp so that units
// without the dialog headers' statics (shape_file.hpp's unknown_empty_rect) can create
// dialogs: the WOnline page slots.
#ifndef RA2_SHARED_DIALOG_CREATE_HPP
#define RA2_SHARED_DIALOG_CREATE_HPP

#include "shared/win32_api.hpp"

typedef int (WINAPI *DialogProc)(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

HWND __fastcall unknown_create_dialog_5ff610(int resource, DialogProc proc, int unknown3);  // 0x005FF610

bool unknown_6000d0();                                                               // 0x006000D0 ends the wait when true

#endif
