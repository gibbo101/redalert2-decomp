// HRESULT __stdcall CChatEventSink::OnSetLocale(HRESULT result, int locale) (0x00764F80, slot 35)
// Records the local player's new locale under the lower-case nickname (replacing an older entry).
#include "shared/wol_sink.hpp"
// @ref ??_GNode@?$WolDictionary@VWstring@@H@@QAEPAXI@Z=007667a0
// @ref ?Shrink_Table@?$WolDictionary@VWstring@@H@@QAEXXZ=00767850
// @ref ?Grow_Table@?$WolDictionary@VWstring@@H@@QAEXXZ=00767900

HRESULT __stdcall CChatEventSink::OnSetLocale(HRESULT result, int locale)
{
    Wstring name;
    char nick[64];
    strcpy(nick, unknown_name_a3d3a0);
    name.Set(nick);
    name.To_Lower();
    if (unknown_channel_names_b293a0.Contains(name)) unknown_channel_names_b293a0.Remove(name);
    unknown_channel_names_b293a0.Add(name, locale);
    return S_OK;
}
