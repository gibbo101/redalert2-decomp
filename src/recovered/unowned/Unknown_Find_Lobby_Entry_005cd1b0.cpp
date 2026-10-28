// UnknownPlayerEntry *__fastcall Unknown_Find_Lobby_Entry_005cd1b0(WideString const &name) (0x005CD1B0)
// The fixed lobby entry whose name equals the narrowed name; null when name is not narrow or matches none.
#include "shared/lobby.hpp"
#include "shared/wide_string.hpp"
// @ref ?unknown_player_a72d44@@3PAUUnknownPlayerEntry@@A=00a72d44
// @ref ?unknown_lobby_entries_a72d2c@@3PAPAUUnknownPlayerEntry@@A=00a72d2c
// @ref ?unknown_lobby_names_7e6de8@@3PAPBDA=007e6de8
// @ref ??8Wstring@@QBE_NPBD@Z=0076da00

UnknownPlayerEntry *__fastcall Unknown_Find_Lobby_Entry_005cd1b0(WideString const &name)
{
    if (name.Is_Narrow()) {
        Wstring narrow = Narrow_Copy_00771280(name);
        if (narrow == unknown_lobby_names_7e6de8[0]) {
            return unknown_lobby_entries_a72d2c[0];
        }
        if (narrow == unknown_lobby_names_7e6de8[1]) {
            return unknown_lobby_entries_a72d2c[1];
        }
        if (narrow == unknown_lobby_names_7e6de8[2]) {
            return unknown_lobby_entries_a72d2c[5];
        }
        if (narrow == unknown_lobby_names_7e6de8[3]) {
            return unknown_lobby_entries_a72d2c[2];
        }
        if (narrow == unknown_lobby_names_7e6de8[4]) {
            return unknown_lobby_entries_a72d2c[3];
        }
        if (narrow == unknown_lobby_names_7e6de8[5]) {
            return unknown_lobby_entries_a72d2c[4];
        }
        if (narrow == unknown_lobby_names_7e6de8[6]) {
            return unknown_player_a72d44;
        }
    }
    return 0;
}
