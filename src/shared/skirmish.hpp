// Skirmish.cpp ("D:\Ra2\Skirmish.cpp"; unit 0x00682600-0x006846BF): the
// skirmish setup dialog (resource 0x102). Players 1-7 are chosen in combo
// boxes 0x50B, 0x50E, 0x516, 0x51A, 0x51B, 0x51C and 0x51D whose item data is
// the player type: -1 none, 0 genius, 1 smart, 2 dumb computer
// (STT:Player<Type>). Names are hypotheses.
#ifndef RA2_SHARED_SKIRMISH_HPP
#define RA2_SHARED_SKIRMISH_HPP

#include "shared/win32_api.hpp"

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

extern HWND SkirmishDialog;   // 0x00ABCDFC (while the dialog runs)

// The player-type combo box id of player index + 1 (index 0-6), or -1, and the
// inverse (out-of-line copies are unreferenced; the dialog code expands them).
int __fastcall Skirmish_Player_Combo_ID(int index);                         // 0x006827F0
int __fastcall Skirmish_Player_Index(int id);                               // 0x00682850
wchar_t const *__fastcall Skirmish_Player_Type_Name(int type);              // 0x006828B0
// Whether a player from `player` on is a computer player.
bool __fastcall Skirmish_Has_Computer_After(int player);                    // 0x00682930
// Whether the player-type combo box `id` selects a computer player.
BOOL __fastcall Skirmish_Is_Computer(HWND dialog, int id);                  // 0x006836B0
// Shows the rows of `count` players from `first` and enables their side and
// colour boxes for computer players only (resetting them otherwise).
void __fastcall Skirmish_Show_Players(HWND dialog, int first, int count);  // 0x006836F0
// Resets the rows of the players from `first` on to "none" and hides them.
void __fastcall Skirmish_Hide_Players(HWND dialog, int first);              // 0x00683920

#endif
