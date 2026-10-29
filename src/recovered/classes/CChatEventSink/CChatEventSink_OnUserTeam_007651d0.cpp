// HRESULT __stdcall CChatEventSink::OnUserTeam(HRESULT result, WOL::User *users) (0x007651D0, slot 34)
// Records each user's team by name (replacing an older entry), then continues the pending queries.
#include "shared/wol_sink.hpp"
// @ref ?unknown_known_names_b294b8=00b294b8

HRESULT __stdcall CChatEventSink::OnUserTeam(HRESULT result, WOL::User *users)
{
    if (result >= 0) {
        WOL::User *user = users;
        Wstring name;
        while (user) {
            name.Set(user->name);
            if (unknown_known_names_b294b8.Contains(name)) unknown_known_names_b294b8.Remove(name);
            unknown_known_names_b294b8.Add(name, user->team);
            user = user->next;
        }
        Unknown_0073FEE0(0, false);
        return S_OK;
    }
    Debug_Printf("OnUserTeam FAILED!\n");
    return S_OK;
}
// @ref ??_C@_0BE@CJNE@OnUserTeam?5FAILED?$CB?6?$AA@=007fe370
// @ref ??_GNode@?$WolDictionary@VWstring@@H@@QAEPAXI@Z=007667a0
// @ref ?Shrink_Table@?$WolDictionary@VWstring@@H@@QAEXXZ=00767850
// @ref ?Grow_Table@?$WolDictionary@VWstring@@H@@QAEXXZ=00767900
