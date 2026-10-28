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
int __fastcall unknown_player_control_4d1000(int player);      // 0x004D1000 (0x754-0x75B)
// The ping image of a connection quality 0-2 (0x004D0FB0), and a player row's ping
// control set to it (0x004D1060).
class Surface;
Surface *__fastcall Ping_Image_4d0fb0(int ping);
void __fastcall Set_Player_Ping_4d1060(HWND dialog, int player, int ping);
int __fastcall Player_Side_Combo_ID_4d1350(int player);        // 0x004D1350 (0x6A1, ...)
// Shows the flag of the country chosen in a player row (0x004D1230).
void __fastcall Show_Player_Flag_4d1230(HWND dialog, int player);
int __fastcall Player_Color_Combo_ID_4d1cb0(int player);       // 0x004D1CB0 (0x6A2, ...)
// The player of a side / colour combo box id (the inverse of the two above), or -1.
int __fastcall unknown_control_player_4d0f40(int id);          // 0x004D0F40 (the inverse of 0x004D0EE0)
int __fastcall Side_Combo_Player_4d13b0(int id);               // 0x004D13B0
int __fastcall Color_Combo_Player_4d1d10(int id);              // 0x004D1D10
// The item data of a side / colour combo box's item (index -1: the selection).
int __fastcall Side_Combo_Data_4d1c70(HWND dialog, int id, int index);    // 0x004D1C70
int __fastcall Color_Combo_Data_4d2900(HWND dialog, int id, int index);   // 0x004D2900
// The text of a side (STT:PlayerSide<Country>) and of a colour (STT:PlayerColor<Colour>).
wchar_t const *__fastcall Side_Name_4d1420(int side);          // 0x004D1420
// Fill a side combo box: "GUI:RandomEx" and the multiplayer countries (0x004D1560),
// or "GUI:Observer" alone (0x004D1640).
void __fastcall Fill_Side_Combo_4d1560(HWND dialog, int id);
void __fastcall Fill_Observer_Combo_4d1640(HWND dialog, int id);
// Fills every player row's side combo box (0x004D16D0): the observer entry
// alone for a row whose player combo box (id = the row) holds 0x00A72D44.
void __fastcall Fill_Side_Combos_4d16d0(HWND dialog);
// The item data of a combo box item (-1: the selection), 0 instead of CB_ERR
// (0x005C99D0, the multiplayer dialogs' unit).
int __fastcall unknown_combo_selected_data_005c99d0(HWND dialog, int id, int index);
wchar_t const *__fastcall Color_Name_4d1d80(int color);        // 0x004D1D80
// Selects an item of a player's colour or side combo box by value (-2 by the
// skirmish dialog when the row is not a computer player).
void __fastcall Select_Color_Combo_4d2480(HWND dialog, int id, int color);   // 0x004D2480
void __fastcall Select_Side_Combo_4d1a90(HWND dialog, int id, int side);     // 0x004D1A90
void __fastcall Select_Player_Side_4d1820(HWND dialog, int player);    // 0x004D1820 (the session player's country)

// The dialogs' colour table (0x008660D8, nine entries: the colour's abbreviated
// name, its value and the combo box item showing it, -1 for none) and the
// colour values (0x007E6D94, RGB). Filled by 0x004D1EA0.
struct UnknownColorEntry {
    wchar_t const *Name;    // +0x00
    int Color;              // +0x04
    int Index;              // +0x08
};
extern UnknownColorEntry unknown_color_entries_8660d8[9];
extern int const unknown_color_values_7e6d94[9];
void __fastcall Init_Color_Entries_4d1ea0();
int __fastcall Color_Entry_Of_Combo_4d1fc0(int id);           // 0x004D1FC0 (the entry a colour combo box's row holds, or -1)
bool __fastcall Color_Entry_Taken_4d2060(int entry);           // 0x004D2060
// Fill a colour combo box with the free colours and the row's own (0x004D2080),
// or with the random entry alone (0x004D2250).
void __fastcall Fill_Color_Combo_4d2080(HWND dialog, int id);
void __fastcall Fill_Random_Color_Combo_4d2250(HWND dialog, int id);
void __fastcall Fill_Color_Combos_4d2300(HWND dialog);          // 0x004D2300 (every player row)
void __fastcall Select_Player_Color_4d23c0(HWND dialog, int player);   // 0x004D23C0 (the session player's colour)
void __fastcall Color_Combo_Changed_4d2700(HWND dialog, int id);       // 0x004D2700 (a row's colour selection changed)

#endif
