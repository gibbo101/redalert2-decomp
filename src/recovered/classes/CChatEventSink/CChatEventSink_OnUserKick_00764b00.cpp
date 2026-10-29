// HRESULT __stdcall CChatEventSink::OnUserKick(HRESULT result, WOL::Channel *channel, WOL::User *kicked, WOL::User *kicker) (0x00764B00, slot 24)
// Reports a kick: to the kicked local user as a popup (or in the game lobby's list), to others in
// the chat unless the game slots are full; then drops the kicked user and refreshes the lists.
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/crt_tokens.hpp"
// @ref ?unknown_b2abd9@@3_NA=00b2abd9
// @ref ?unknown_kick_channel_b2b3c0@@3PADA=00b2b3c0
// @ref ?unknown_lobby_names_b26c94@@3PAPADA=00b26c94
// @ref ?unknown_b2abec@@3HA=00b2abec
// @ref __strnicmp=007858d0
// @ref _atol=00782d72
// @ref _sprintf=007820f4
// @ref ?Unknown_006FA180=006fa180
// @ref ?unknown_color_7a7360=007a7360
// @ref ?Unknown_005C2C80@@YAXHPBGZZ=005c2c80
// @ref ?Unknown_0073c120=0073c120

HRESULT __stdcall CChatEventSink::OnUserKick(HRESULT result, WOL::Channel *channel, WOL::User *kicked, WOL::User *kicker)
{
    if (unknown_b2abd9) return S_OK;
    if (result < 0) return S_OK;
    memset(unknown_kick_channel_b2b3c0, 0, sizeof(unknown_kick_channel_b2b3c0));
    char const *name = channel->name;
    if (!_strnicmp(name, "Lob_33_", strlen("Lob_33_"))) {
        int number = atol(channel->name + strlen("Lob_33_"));
        int group = number / 8;
        int index = number % 8;
        if (group == 0) {
            sprintf(unknown_kick_channel_b2b3c0, "%s", unknown_lobby_names_b26c94[index]);
        } else {
            sprintf(unknown_kick_channel_b2b3c0, "%s %d", unknown_lobby_names_b26c94[index], group + 1);
        }
    } else {
        sprintf(unknown_kick_channel_b2b3c0, "%s", name);
    }
    if (kicked->flags & 0x8000) {
        WideString text;
        if (unknown_b299c0 && Channel_Full_005c9510()) {
            text = StringTable::Load_String("TXT_CHANNEL_FULL", 0, "D:\\Ra2\\wonline.cpp", 0x1db7);
        } else {
            wchar_t buffer[1024];
            memset(buffer, 0, sizeof(buffer));
            swprintf(buffer, StringTable::Load_String("TXT_YOURE_KICKED", 0, "D:\\Ra2\\wonline.cpp", 0x1dbb), Unknown_006FA180(name), Unknown_006FA180(kicker->name));
            text = buffer;
        }
        if (!unknown_b299c0) {
            Popup_005c3230(text.Get(), 0, Unknown_0073c120, 0);
            ++unknown_b2abec;
        } else {
            HWND dialog = (HWND)Unknown_00735940(0x113);
            if (dialog) Unknown_005C2DA0(unknown_color_7a7360, text.Get(), GetDlgItem(dialog, 0x53f));
        }
    } else if (!Slots_Filled_005c9440()) {
        Unknown_005C2C80(unknown_color_7a7360, StringTable::Load_String("TXT_USER_KICKED", 0, "D:\\Ra2\\wonline.cpp", 0x1dd3), Unknown_006FA180(kicked->name), Unknown_006FA180(name), Unknown_006FA180(kicker->name));
    }
    Unknown_00741750(kicked);
    Unknown_0073FEE0(0, false);
    Unknown_0073f8f0();
    return S_OK;
}
// @ref ??_C@_0BA@NNBL@TXT_USER_KICKED?$AA@=007fe304
// @ref ??_C@_0BB@KGDC@TXT_YOURE_KICKED?$AA@=007fe314
// @ref ??_C@_0BB@MMLP@TXT_CHANNEL_FULL?$AA@=007fde60
// @ref ??_C@_05GGPB@?$CFs?5?$CFd?$AA@=007fe1c0
// @ref ??_C@_07HCKM@Lob_33_?$AA@=007fd358
// @ref ??_C@_02DILL@?$CFs?$AA@=007e7f2c
