// Wstring __fastcall Unknown_Lobby_Entry_Name_005cd0e0(NodeNameType *entry) (0x005CD0E0)
// The name of a fixed lobby entry (Open, Closed, EasyAI, MediumAI, HardAI, OpenObserver);
// "Waiting" for the waiting entry and for every other entry.
#include "shared/lobby.hpp"
// @ref ?unknown_player_a72d44@@3PAUNodeNameType@@A=00a72d44
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c
// @ref ?unknown_closed_entry_a72d30@@3PAUNodeNameType@@A=00a72d30
// @ref ?unknown_easy_ai_entry_a72d34@@3PAUNodeNameType@@A=00a72d34
// @ref ?unknown_medium_ai_entry_a72d38@@3PAUNodeNameType@@A=00a72d38
// @ref ?unknown_hard_ai_entry_a72d3c@@3PAUNodeNameType@@A=00a72d3c
// @ref ?unknown_waiting_entry_a72d40@@3PAUNodeNameType@@A=00a72d40
// @ref ?unknown_lobby_names_7e6de8@@3PAPBDA=007e6de8

Wstring __fastcall Unknown_Lobby_Entry_Name_005cd0e0(NodeNameType *entry)
{
    if (entry == unknown_open_entry_a72d2c) {
        return Wstring(unknown_lobby_names_7e6de8[0]);
    }
    if (entry == unknown_closed_entry_a72d30) {
        return Wstring(unknown_lobby_names_7e6de8[1]);
    }
    if (entry == unknown_waiting_entry_a72d40) {
        return Wstring(unknown_lobby_names_7e6de8[2]);
    }
    if (entry == unknown_easy_ai_entry_a72d34) {
        return Wstring(unknown_lobby_names_7e6de8[3]);
    }
    if (entry == unknown_medium_ai_entry_a72d38) {
        return Wstring(unknown_lobby_names_7e6de8[4]);
    }
    if (entry == unknown_hard_ai_entry_a72d3c) {
        return Wstring(unknown_lobby_names_7e6de8[5]);
    }
    if (entry == unknown_player_a72d44) {
        return Wstring(unknown_lobby_names_7e6de8[6]);
    }
    return Wstring(unknown_lobby_names_7e6de8[2]);
}
