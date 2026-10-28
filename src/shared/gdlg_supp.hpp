// GDlgSupp.cpp ("D:\Ra2\GDlgSupp.cpp"; unit 0x004D0CF0-0x004D2A10): helpers the
// skirmish and multiplayer setup dialogs share. Players 0-7 each have a row of
// dialog controls; these map a player to a control id and back, fill and
// select the side (country) and colour combo boxes, and name a side or colour
// (STT:PlayerSide<Country>, STT:PlayerColor<Colour>). Only the functions the
// recovered callers use are declared; their names are hypotheses from the ids
// and strings.
#ifndef RA2_SHARED_GDLG_SUPP_HPP
#define RA2_SHARED_GDLG_SUPP_HPP

#include "shared/win32_api.hpp"

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

// A player's control ids (player 0-7; -1 for any other value).
int __fastcall unknown_player_control_4d0ee0(int player);      // 0x004D0EE0 (0x6DA-0x6E1)
int __fastcall Player_Side_Combo_ID_4d1350(int player);        // 0x004D1350 (0x6A1, ...)
int __fastcall Player_Color_Combo_ID_4d1cb0(int player);       // 0x004D1CB0 (0x6A2, ...)
// The player of a side / colour combo box id (the inverse of the two above), or -1.
int __fastcall Side_Combo_Player_4d13b0(int id);               // 0x004D13B0
int __fastcall Color_Combo_Player_4d1d10(int id);              // 0x004D1D10
// The item data of a side / colour combo box's item (index -1: the selection).
int __fastcall Side_Combo_Data_4d1c70(HWND dialog, int id, int index);    // 0x004D1C70
int __fastcall Color_Combo_Data_4d2900(HWND dialog, int id, int index);   // 0x004D2900
// The text of a side (STT:PlayerSide<Country>) and of a colour (STT:PlayerColor<Colour>).
wchar_t const *__fastcall Side_Name_4d1420(int side);          // 0x004D1420
wchar_t const *__fastcall Color_Name_4d1d80(int color);        // 0x004D1D80
// Selects an item of a player's colour or side combo box by value (-2 by the
// skirmish dialog when the row is not a computer player).
void __fastcall Select_Color_Combo_4d2480(HWND dialog, int id, int color);   // 0x004D2480
void __fastcall Select_Side_Combo_4d1a90(HWND dialog, int id, int side);     // 0x004D1A90

#endif
