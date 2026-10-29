// NodeNameType *__fastcall Unknown_Find_Lobby_Entry_005cd1b0(WideString const &name) (0x005CD1B0)
// The fixed lobby entry whose name equals the narrowed name; null when name is not narrow or matches none.
#include "shared/lobby.hpp"
#include "shared/wide_string.hpp"
// @ref ?unknown_player_a72d44@@3PAUNodeNameType@@A=00a72d44
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c
// @ref ?unknown_closed_entry_a72d30@@3PAUNodeNameType@@A=00a72d30
// @ref ?unknown_easy_ai_entry_a72d34@@3PAUNodeNameType@@A=00a72d34
// @ref ?unknown_medium_ai_entry_a72d38@@3PAUNodeNameType@@A=00a72d38
// @ref ?unknown_hard_ai_entry_a72d3c@@3PAUNodeNameType@@A=00a72d3c
// @ref ?unknown_waiting_entry_a72d40@@3PAUNodeNameType@@A=00a72d40
// @ref ?unknown_lobby_names_7e6de8@@3PAPBDA=007e6de8
// @ref ??8Wstring@@QBE_NPBD@Z=0076da00

NodeNameType *__fastcall Unknown_Find_Lobby_Entry_005cd1b0(WideString const &name)
{
    if (name.Is_Narrow()) {
        Wstring narrow = Narrow_Copy_00771280(name);
        if (narrow == unknown_lobby_names_7e6de8[0]) {
            return unknown_open_entry_a72d2c;
        }
        if (narrow == unknown_lobby_names_7e6de8[1]) {
            return unknown_closed_entry_a72d30;
        }
        if (narrow == unknown_lobby_names_7e6de8[2]) {
            return unknown_waiting_entry_a72d40;
        }
        if (narrow == unknown_lobby_names_7e6de8[3]) {
            return unknown_easy_ai_entry_a72d34;
        }
        if (narrow == unknown_lobby_names_7e6de8[4]) {
            return unknown_medium_ai_entry_a72d38;
        }
        if (narrow == unknown_lobby_names_7e6de8[5]) {
            return unknown_hard_ai_entry_a72d3c;
        }
        if (narrow == unknown_lobby_names_7e6de8[6]) {
            return unknown_player_a72d44;
        }
    }
    return 0;
}
