// The common owner-draw dialog procedure (0x005FFB00), split out of shared/ms_message_box.hpp
// (which includes it where it declared it) for dialog units without the message box headers'
// statics (shape_file.hpp's unknown_empty_rect): the keyboard dialog in Options.CPP.
#ifndef RA2_SHARED_DIALOG_DEFAULT_PROC_HPP
#define RA2_SHARED_DIALOG_DEFAULT_PROC_HPP

#include "shared/win32_api.hpp"

// Every dialog procedure runs it first; nonzero when it handled the message.
int __fastcall unknown_dialog_proc_5ffb00(HWND window, UINT message, WPARAM wparam, LPARAM lparam);  // 0x005FFB00

#endif
