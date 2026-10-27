// HRESULT __stdcall CChatEventSink::OnPublicAction(HRESULT result, WOL::Channel *channel, WOL::User *user, char const *action) (0x00764500, slot 14)
// Shows "<nick> <action>" for a visible action from another user.
#include "shared/wol_sink.hpp"
// @ref ?unknown_b2abd9@@3_NA=00b2abd9
// @ref ??0Wstring@@QAE@PBD@Z=0076d920
// @ref ??1Wstring@@QAE@XZ=0076d9e0
// @ref ?Wstring_To_Wide@@YI?AVWideString@@ABVWstring@@@Z=007711c0
// @ref ?Get@WideString@@QBEPBGXZ=007703f0
// @ref ??1WideString@@QAE@XZ=0076fa50
// @ref __stricmp=00781f20
// @ref ?unknown_name_a3d3a0@@3PADA=00a3d3a0
// @ref ?unknown_color_7a7370@@3HA=007a7370
// @ref ?unknown_b2a7e8@@3HA=00b2a7e8
// @ref ?Unknown_00735940@@YIPAXH@Z=00735940
// @ref ?Unknown_005C2C80@@YAXHPBGZZ=005c2c80

HRESULT __stdcall CChatEventSink::OnPublicAction(HRESULT result, WOL::Channel *channel, WOL::User *user, char const *action)
{
    if (!unknown_b2abd9 && result >= 0) {
        bool show;
        {
            // Unused copy of the text (hypothesis: left over from a removed check).
            Wstring copy(action);
            if (!user) {
                show = false;
            } else if (user->flags & 1) {
                show = true;
            } else if (Unknown_00735940(0xC2)) {
                show = true;
            } else if (Unknown_00735940(0xC9)) {
                show = true;
            } else {
                show = unknown_b2a7e8 != 0;
            }
        }
        if (show) {
            WideString text = Wstring_To_Wide(action);
            if (_stricmp(unknown_name_a3d3a0, user->name)) {
                Unknown_005C2C80(unknown_color_7a7370, L"%hs %s", user->name, text.Get());
            }
        }
    }
    return S_OK;
}
// @ref ??_C@_1O@MAMF@?$AA?$CF?$AAh?$AAs?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007fe2c4
