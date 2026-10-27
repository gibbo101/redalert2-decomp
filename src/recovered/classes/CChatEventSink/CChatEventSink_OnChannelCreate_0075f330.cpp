#include "shared/wol_sink.hpp"
static inline void Complete_Channel_Create_Request()
{
    void *dialog = Unknown_00735940(0xc4);
    if (dialog && (unknown_b2abe0 &= ~4u) == 0) Unknown_007357E0(dialog, 0);
    HWND window = Unknown_00735B10();
    window = GetDlgItem(window, 0x540);
    if (window) SetFocus(window);
}
HRESULT __stdcall CChatEventSink::OnChannelCreate(HRESULT result, WOL::Channel *channel)
{
    char user_options[80];
    if (result < 0) {
        Unknown_005C2C80(unknown_color_7a7360, StringTable::Load_String("TXT_CHANCREATE_FAILED", 0, "D:\\Ra2\\wonline.cpp", 0x1212));
        unknown_b2ac58 = 0;
        unknown_channel_b299c0.name[0] = 0;
        Complete_Channel_Create_Request();
        return S_OK;
    } else {
        if (channel->unknown_00 == 0) {
            Unknown_005C2C80(unknown_color_7a7360, StringTable::Load_String("TXT_CREATED_CHAN", 0, "D:\\Ra2\\wonline.cpp", 0x121c), Unknown_006FA180(channel->name));
        } else {
            memset(unknown_player_b29cf0, 0, sizeof(unknown_player_b29cf0));
            char const *name = unknown_wstring_b26cb8.Get();
            strcpy(unknown_player_b29cf0[0].name, name);
            unknown_player_b29cf0[0].unknown_18 = unknown_a3d3bc;
            unknown_player_b29cf0[0].unknown_1c = 0;
            unknown_player_b29cf0[0].unknown_14 = unknown_a3d3b4;
            unknown_player_b29cf0[0].unknown_20 = 1;
        }
        unknown_channel_b299c0 = *channel;
        unknown_b2ac58 = 1;
        ++unknown_b2abe8;
        Debug_Printf("Created channel\n");
        if (unknown_chat_a72cfc && channel->unknown_00 != 0) {
            memset(user_options, 0, sizeof(user_options));
            Format_User_Options_0073cff0(user_options);
            user_options[40] = 0;
            unknown_chat_a72cfc->unknown_slot42(user_options);
        }
        Complete_Channel_Create_Request();
    }
    return S_OK;
}
// @ref ?unknown_player_b29cf0=00b29cf0
// @ref ?unknown_channel_b299c0=00b299c0
// @ref ?unknown_chat_a72cfc=00a72cfc
// @ref ?unknown_wstring_b26cb8=00b26cb8
// @ref ?unknown_a3d3bc=00a3d3bc
// @ref ?unknown_a3d3b4=00a3d3b4
// @ref ?unknown_b2ac58=00b2ac58
// @ref ?unknown_b2abe8=00b2abe8
// @ref ?Format_User_Options_0073cff0=0073cff0
// @ref ?Unknown_006FA180=006fa180
// @ref ??_C@_0BB@CMCH@Created?5channel?6?$AA@=007fdda0
// @ref ??_C@_0BB@MOKA@TXT_CREATED_CHAN?$AA@=007fddb4
// @ref ??_C@_0BG@BAEL@TXT_CHANCREATE_FAILED?$AA@=007fddc8

// @ref ??_C@_0BD@IJO@D?3?2Ra2?2wonline?4cpp?$AA@=007fd62c
