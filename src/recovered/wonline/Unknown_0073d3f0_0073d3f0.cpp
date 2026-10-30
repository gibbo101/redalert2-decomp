// int __fastcall Unknown_0073d3f0(Wstring const &name) (0x0073D3F0)
// The session player number of a WOL nickname (empty: the local nickname): 1 for the host, else +0x67 of the
// session player entry with that name (case-insensitive), -1 when there is none.
#include "shared/wol_sink.hpp"
#include "shared/unknown_player_entry.hpp"

int __fastcall Unknown_0073d3f0(Wstring const &name)
{
    Wstring nick(name.Length() > 0 ? name : unknown_wstring_b26cb8);
    Wstring lower = nick.As_Lower();
    if (Wstring_To_Wide(lower) == WideString(unknown_host_name_a3f618).As_Lower()) {
        return 1;
    }
    int found = -1;
    for (int index = 0; index < unknown_players_a3fa7c.Count(); index++) {
        Wstring player = Narrow_Copy_00771280(unknown_players_a3fa7c[index]->Name);
        if (player.As_Lower() == lower) found = index;
    }
    if (found != -1) {
        return unknown_players_a3fa7c[found]->unknown_67;
    }
    return -1;
}
