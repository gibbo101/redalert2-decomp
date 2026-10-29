// The save and load game dialog helpers (LoadDlg.CPP, 0x0053B770-0x0053C9E7; the file name is the debug string at
// 0x007DFAA4). Red Alert's LOADDLG.CPP holds the same helpers (Fill_List, Num_Games, Load/Save dialogs); the names
// here are hypotheses.
#ifndef RA2_SHARED_LOAD_DLG_HPP
#define RA2_SHARED_LOAD_DLG_HPP

#include "shared/win32_api.hpp"
#include "shared/mouse.hpp"
#include "shared/string_table.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/file_entry.hpp"
#include "shared/map_seed.hpp"
#include "shared/win32_find.hpp"
#include "shared/savegame_info.hpp"

// The dialog helpers of shared/ms_message_box.hpp, repeated here because that header pulls in wwmouse.hpp's
// static empty rect (population-20 units compile separately and must not emit a header initializer).
HWND __fastcall unknown_cancel_dialog_6001e0(unsigned short const *text, unsigned short const *button, bool *cancelled);
void __fastcall unknown_dialog_5ff7c0(HWND window);
void __fastcall unknown_dialog_5ff6e0(HWND window);

extern int unknown_savegame_version_7f1b18;   // 0x007F1B18 (a saved game with another first value is flagged)
extern bool unknown_flag_a40380;  // 0x00A40380
WIN32_IMPORT LONG WINAPI CompareFileTime(FILETIME const *first, FILETIME const *second);   // KERNEL32

// Compares the write times of two save file entries (qsort callback; newest first) (0x0053C650).
int __cdecl Compare_Save_Times(FileEntryClass **first, FileEntryClass **second);
// Runs a load or save under the "loading" / "saving" dialog (0x0053C680, 0x0053C760).
bool __stdcall Load_Game_With_Dialog(char const *filename);
bool __stdcall Save_Game_With_Dialog(char const *filename, wchar_t const *description);
bool __stdcall Delete_Save_File(char const *filename);                                   // 0x0053C7D0

bool __fastcall Unknown_00656890(char const *filename);                                  // 0x00656890
bool __fastcall Unknown_006554A0(char const *filename, wchar_t const *description, int unknown);   // 0x006554A0
extern "C" int __cdecl _stricmp(char const *first, char const *second);                  // 0x00781F20

#endif
