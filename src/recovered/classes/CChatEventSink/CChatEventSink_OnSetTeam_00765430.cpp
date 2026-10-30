// HRESULT __stdcall CChatEventSink::OnSetTeam(HRESULT result, int team) (0x00765430, slot 36)
// Stores the local player's new team and records it under the lower-case nickname.
// On failure it prints the team, not the result (original behaviour).
#include "shared/wol_sink.hpp"
// @ref ?unknown_a3d3bc=00a3d3bc
// @ref ??_GNode@?$WolDictionary@VWstring@@H@@QAEPAXI@Z=007667a0
// @ref ?Shrink_Table@?$WolDictionary@VWstring@@H@@QAEXXZ=00767850
// @ref ?Grow_Table@?$WolDictionary@VWstring@@H@@QAEXXZ=00767900

HRESULT __stdcall CChatEventSink::OnSetTeam(HRESULT result, int team)
{
    if (result == S_OK) {
        unknown_a3d3bc = team;
        Wstring name;
        char nick[64];
        strcpy(nick, unknown_name_a3d3a0);
        name.Set(nick);
        name.To_Lower();
        if (unknown_known_names_b294b8.Contains(name)) unknown_known_names_b294b8.Remove(name);
        unknown_known_names_b294b8.Add(name, team);
        return S_OK;
    }
    Debug_Printf("OnSetTeam FAILED: %d\n", team);
    return S_OK;
}
// @ref ??_C@_0BG@KNAI@OnSetTeam?5FAILED?3?5?$CFd?6?$AA@=007fe384
// @ref ?unknown_known_names_b294b8=00b294b8
