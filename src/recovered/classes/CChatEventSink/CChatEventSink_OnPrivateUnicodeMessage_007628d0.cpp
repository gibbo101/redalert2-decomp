// HRESULT __stdcall CChatEventSink::OnPrivateUnicodeMessage(HRESULT result, WOL::User *user, unsigned short const *message) (0x007628D0, slot 41)
// Shows "<nick> : <message>" for a visible wide-text private message from another user.
#include "shared/wol_sink.hpp"
#include "shared/wol_settings.hpp"
// @ref ?unknown_b2abd9@@3_NA=00b2abd9
// @ref ??0WideString@@QAE@PBG@Z=0076f9c0
// @ref ?Is_Narrow@WideString@@QBE_NXZ=00771080
// @ref ?Get@WideString@@QBEPBGXZ=007703f0
// @ref ??1WideString@@QAE@XZ=0076fa50
// @ref __stricmp=00781f20
// @ref ?unknown_name_a3d3a0@@3PADA=00a3d3a0
// @ref ?unknown_color_7a7368@@3HA=007a7368
// @ref ?unknown_color_7a7374@@3HA=007a7374
// @ref ?unknown_wol_display_latin_b2a7e8@@3HA=00b2a7e8
// @ref ?unknown_wol_display_asian_b2a804@@3HA=00b2a804
// @ref ?Unknown_00735940@@YIPAXH@Z=00735940
// @ref ?Unknown_005C2C80@@YAXHPBGZZ=005c2c80

HRESULT __stdcall CChatEventSink::OnPrivateUnicodeMessage(HRESULT result, WOL::User *user, unsigned short const *message)
{
    if (unknown_b2abd9) return S_OK;
    if (result < 0) return S_OK;
    WideString text(message);
    bool show;
    if (!user) {
        show = false;
    } else if (user->flags & 1) {
        show = true;
    } else if (Unknown_00735940(0xC2)) {
        show = true;
    } else if (Unknown_00735940(0xC9)) {
        show = true;
    } else {
        show = (text.Is_Narrow() ? unknown_wol_display_latin_b2a7e8 : unknown_wol_display_asian_b2a804) != 0;
    }
    if (!show) return S_OK;
    int color = unknown_color_7a7368;
    if (user->flags & 1) color = unknown_color_7a7374;
    if (_stricmp(unknown_name_a3d3a0, user->name)) {
        Unknown_005C2C80(color, L"%hs : %s", user->name, text.Get());
    }
    return S_OK;
}
// @ref ??_C@_1BC@JGAD@?$AA?$CF?$AAh?$AAs?$AA?5?$AA?3?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007fe07c
