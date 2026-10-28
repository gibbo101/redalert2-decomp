// The multiplayer lobby's slot tables (Lobby code around 0x005C8950-0x005CF000;
// names are hypotheses from the slot logic). Seven fixed lobby entries (open,
// closed, computer, ...: UnknownPlayerEntry-shaped records) and eight player slots,
// each pointing at one of those entries or at a session node.
#ifndef RA2_SHARED_LOBBY_HPP
#define RA2_SHARED_LOBBY_HPP

#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/unknown_player_entry.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/wstring.hpp"
#include "shared/network_tests.hpp"
#include "shared/win32_api.hpp"
#include "shared/wide_string.hpp"

// The first six fixed entries (0x00A72D2C..0x00A72D40); the seventh is unknown_player_a72d44.
// The eight player slots are unknown_player_slots_a3fa98 and the session list unknown_players_a3fa7c.
extern UnknownPlayerEntry *unknown_lobby_entries_a72d2c[6];
// The slot before the table (0x00A3FA94; -1 after a reset).
extern int unknown_lobby_a3fa94;
// Two lobby words cleared by a reset (0x00A728E4, 0x00A72734).
extern unsigned short unknown_lobby_a728e4;
extern unsigned short unknown_lobby_a72734;
// The object at 0x00A3D2B0 (session +0x18) and its member 0x00672810 (hypothesis).
class UnknownLobbyState {
public:
    void Unknown_00672810();                    // 0x00672810
};
extern UnknownLobbyState unknown_lobby_state_a3d2b0;
// Three per-slot setting tables, -1 when a slot is cleared (0x00A3D2DC, 0x00A3D2FC,
// 0x00A3D31C; session +0x44, +0x64, +0x84: AIDifficulty, AICountry, AIColor).
extern int unknown_lobby_a3d2dc[8];
extern int unknown_lobby_a3d2fc[8];
extern int unknown_lobby_a3d31c[8];
// Refreshes one slot's display in the lobby dialog (0x005C9B90; hypothesis).
void __fastcall Unknown_005c9b90(HWND dialog, int slot, int redraw);
// The names of the fixed lobby entries (pointers at 0x007E6DE8..0x007E6E00: "Open",
// "Closed", "Waiting", "EasyAI", "MediumAI", "HardAI", "OpenObserver").
extern char const *unknown_lobby_names_7e6de8[7];
// The dialog manager's current dialog ID (0x00735B20) and the dialog window with an ID, or 0
// (0x00735940); hypotheses from the one lobby caller.
int Current_Dialog_Id_00735b20();
HWND __fastcall Find_Dialog_00735940(int id);
// 0 until the lobby is set up (0x007E6D90, initialised -1; hypothesis).
extern int unknown_lobby_flag_7e6d90;

// Wide-string comparison, 0 when equal (0x007837D3; the CRT's _wcsicmp).
int Compare_Wide_007837d3(wchar_t const *first, wchar_t const *second);
// Narrows a wide string into a rotating buffer (0x006FA120).
char *__fastcall Unknown_006FA120(unsigned short const *string);
// Widens a narrow string into a rotating buffer (0x006FA180).
wchar_t *__fastcall Unknown_006FA180(char const *text);
// Case-insensitive comparison, 0 when equal (0x00781F20; the CRT's _stricmp).
int Compare_Narrow_00781f20(char const *first, char const *second);
// Frees a block (0x00781D3B; the CRT's free).
void Free_Memory_00781d3b(void *block);
// Frees every element of the list and clears it (0x005A7480).
void __fastcall Free_Pointers_005a7480(DynamicVectorClass<UnknownPlayerEntry *> *list);

// The index-matched player's value (+0x67) for a nick name, 1 for the host's own name, -1 when unknown (0x005BCC60).
int __fastcall Unknown_Find_Player_By_Name_005bcc60(char const *name);

// The name of a fixed lobby entry ("Waiting" for any other entry; 0x005CD0E0).
Wstring __fastcall Unknown_Lobby_Entry_Name_005cd0e0(UnknownPlayerEntry *entry);

#endif
