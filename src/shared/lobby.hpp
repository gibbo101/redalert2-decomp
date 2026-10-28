// The multiplayer lobby's slot tables (Lobby code around 0x005C8950-0x005CF000;
// names are hypotheses from the slot logic). Seven fixed lobby entries (open,
// closed, computer, ...: UnknownNodeName-shaped records) and eight player slots,
// each pointing at one of those entries or at a session node.
#ifndef RA2_SHARED_LOBBY_HPP
#define RA2_SHARED_LOBBY_HPP

#include "shared/ipx_manager.hpp"
#include "shared/network_tests.hpp"

// The seven fixed entries (0x00A72D2C..0x00A72D44).
extern UnknownNodeName *unknown_lobby_entries_a72d2c[7];
// The eight player slots (0x00A3FA98..0x00A3FAB4).
extern UnknownNodeName *unknown_lobby_slots_a3fa98[8];
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
// Refreshes the lobby's slot display (0x005C9B90; the argument is 0 here; hypothesis).
void __fastcall Unknown_005c9b90(int redraw);
// 0 until the lobby is set up (0x007E6D90, initialised -1; hypothesis).
extern int unknown_lobby_flag_7e6d90;

// Wide-string comparison, 0 when equal (0x007837D3; the CRT's _wcsicmp).
int Compare_Wide_007837d3(wchar_t const *first, wchar_t const *second);
// Narrows a wide string into a rotating buffer (0x006FA120).
char *__fastcall Unknown_006FA120(unsigned short const *string);
// Case-insensitive comparison, 0 when equal (0x00781F20; the CRT's _stricmp).
int Compare_Narrow_00781f20(char const *first, char const *second);
// Frees a block (0x00781D3B; the CRT's free).
void Free_Memory_00781d3b(void *block);
// Frees every element of the list and clears it (0x005A7480).
void __fastcall Free_Pointers_005a7480(DynamicVectorClass<UnknownNodeName *> *list);

#endif
