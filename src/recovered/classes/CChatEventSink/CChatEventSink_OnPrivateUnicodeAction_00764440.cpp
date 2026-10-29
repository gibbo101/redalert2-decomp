// HRESULT __stdcall CChatEventSink::OnPrivateUnicodeAction(HRESULT result, WOL::User *user, unsigned short const *action) (0x00764440, slot 42)
// Shows "<nick> <action>" for a visible wide-text action from another user.
#include "shared/wol_sink.hpp"
#include "shared/wol_settings.hpp"
// @ref ?unknown_b2abd9@@3_NA=00b2abd9
// @ref ??0WideString@@QAE@PBG@Z=0076f9c0
// @ref ?Is_Narrow@WideString@@QBE_NXZ=00771080
// @ref ??1WideString@@QAE@XZ=0076fa50
// @ref __stricmp=00781f20
// @ref ?unknown_name_a3d3a0@@3PADA=00a3d3a0
// @ref ?unknown_color_7a736c@@3HA=007a736c
// @ref ?unknown_wol_display_latin_b2a7e8@@3HA=00b2a7e8
// @ref ?unknown_wol_display_asian_b2a804@@3HA=00b2a804
// @ref ?Unknown_00735940@@YIPAXH@Z=00735940
// @ref ?Unknown_005C2C80@@YAXHPBGZZ=005c2c80

HRESULT __stdcall CChatEventSink::OnPrivateUnicodeAction(HRESULT result, WOL::User *user, unsigned short const *action)
{
    if (!unknown_b2abd9 && result >= 0) {
        bool show;
        {
            WideString text(action);
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
        }
        if (show) {
            if (_stricmp(unknown_name_a3d3a0, user->name)) {
                Unknown_005C2C80(unknown_color_7a736c, L"%hs %s", user->name, action);
            }
        }
    }
    return S_OK;
}
// @ref ??_C@_1O@MAMF@?$AA?$CF?$AAh?$AAs?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007fe2c4
