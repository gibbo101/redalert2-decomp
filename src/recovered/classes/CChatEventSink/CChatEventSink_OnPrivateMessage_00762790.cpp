// HRESULT __stdcall CChatEventSink::OnPrivateMessage(HRESULT result, WOL::User *user, char const *message) (0x00762790, slot 17)
// In an online game session a message from the channel owner is an in-game message; otherwise
// shows "<nick> : <message>" for a visible private message from another user.
#include "shared/wol_sink.hpp"
// @ref ?unknown_b2abd9@@3_NA=00b2abd9
// @ref ?unknown_a3d2a4@@3HA=00a3d2a4
// @ref ?Unknown_0075B910@@YIXPBD_N@Z=0075b910
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??0Wstring@@QAE@PBD@Z=0076d920
// @ref ??1Wstring@@QAE@XZ=0076d9e0
// @ref ?Wstring_To_Wide@@YI?AVWideString@@ABVWstring@@@Z=007711c0
// @ref ?Get@WideString@@QBEPBGXZ=007703f0
// @ref ??1WideString@@QAE@XZ=0076fa50
// @ref __stricmp=00781f20
// @ref ?unknown_name_a3d3a0@@3PADA=00a3d3a0
// @ref ?unknown_color_7a7368@@3HA=007a7368
// @ref ?unknown_color_7a7374@@3HA=007a7374
// @ref ?unknown_b2a7e8@@3HA=00b2a7e8
// @ref ?Unknown_00735940@@YIPAXH@Z=00735940
// @ref ?Unknown_005C2C80@@YAXHPBGZZ=005c2c80

HRESULT __stdcall CChatEventSink::OnPrivateMessage(HRESULT result, WOL::User *user, char const *message)
{
    if (!unknown_b2abd9 && result >= 0) {
        if (Is_Online_Session()) {
            if (user->flags & 1) {
                Unknown_0075B910(message, true);
                return S_OK;
            }
            Debug_Printf("Received message from non-channel owner %s: %s\n", user->name, message);
            return S_OK;
        }
        bool show;
        {
            // Unused copy of the text (hypothesis: left over from a removed check).
            Wstring copy(message);
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
        if (!show) return S_OK;
        WideString text = Wstring_To_Wide(message);
        int color = unknown_color_7a7368;
        if (user->flags & 1) color = unknown_color_7a7374;
        if (_stricmp(unknown_name_a3d3a0, user->name)) {
            Unknown_005C2C80(color, L"%hs : %s", user->name, text.Get());
        }
    }
    return S_OK;
}
// @ref ??_C@_1BC@JGAD@?$AA?$CF?$AAh?$AAs?$AA?5?$AA?3?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007fe07c
// @ref ??_C@_0DA@BOAL@Received?5message?5from?5non?9channe@=007fe090
