// Wstring __fastcall Unknown_Lobby_Entry_Name_005cd0e0(UnknownPlayerEntry *entry) (0x005CD0E0)
// The name of a fixed lobby entry (Open, Closed, EasyAI, MediumAI, HardAI, OpenObserver);
// "Waiting" for the waiting entry and for every other entry.
#include "shared/lobby.hpp"
// @ref ?unknown_player_a72d44@@3PAUUnknownPlayerEntry@@A=00a72d44
// @ref ?unknown_lobby_entries_a72d2c@@3PAPAUUnknownPlayerEntry@@A=00a72d2c
// @ref ?unknown_lobby_names_7e6de8@@3PAPBDA=007e6de8

Wstring __fastcall Unknown_Lobby_Entry_Name_005cd0e0(UnknownPlayerEntry *entry)
{
    if (entry == unknown_lobby_entries_a72d2c[0]) {
        return Wstring(unknown_lobby_names_7e6de8[0]);
    }
    if (entry == unknown_lobby_entries_a72d2c[1]) {
        return Wstring(unknown_lobby_names_7e6de8[1]);
    }
    if (entry == unknown_lobby_entries_a72d2c[5]) {
        return Wstring(unknown_lobby_names_7e6de8[2]);
    }
    if (entry == unknown_lobby_entries_a72d2c[2]) {
        return Wstring(unknown_lobby_names_7e6de8[3]);
    }
    if (entry == unknown_lobby_entries_a72d2c[3]) {
        return Wstring(unknown_lobby_names_7e6de8[4]);
    }
    if (entry == unknown_lobby_entries_a72d2c[4]) {
        return Wstring(unknown_lobby_names_7e6de8[5]);
    }
    if (entry == unknown_player_a72d44) {
        return Wstring(unknown_lobby_names_7e6de8[6]);
    }
    return Wstring(unknown_lobby_names_7e6de8[2]);
}
