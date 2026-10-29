// int __fastcall Request_To_Join_005bfc40(int game, bool unknown) (0x005BFC40)
#include "shared/lobby.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/string_table.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
#include "shared/session_state.hpp"
// @ref ??_C@_0BD@ELLL@D?3?2Ra2?2netdlg2?4cpp?$AA@=007e69c8
// @ref ??_C@_0BD@KCMF@TXT_GAME_IS_CLOSED?$AA@=007e6c7c
// @ref ??_C@_0BE@CDLH@TXT_NOTHING_TO_JOIN?$AA@=007e6c4c
// @ref ??_C@_0BF@GBEB@TXT_MUST_SELECT_GAME?$AA@=007e6ca0
// @ref ??_C@_0BJ@MAAJ@ERROR?3NameIsReservedWord?$AA@=007e6c60
// @ref ??_C@_0P@FAEG@TXT_NAME_ERROR?$AA@=007e6c90
// @ref ?Unknown_007131b0@UnknownVersionObject@@QAEKXZ=007131b0
// @ref ?Unknown_007131c0@UnknownVersionObject@@QAEKXZ=007131c0
// @ref ?Unknown_00737af0@@YAHXZ=00737af0
// @ref ?Value_011c_00672a10@UnknownSessionState@@QAEHXZ=00672a10
// @ref ?Value_0124_006729f0@UnknownSessionState@@QAEHXZ=006729f0
// @ref ?unknown_a71bc4@@3PADA=00a71bc4
// @ref ?unknown_a71e9c@@3HA=00a71e9c
// @ref ?unknown_a71ea0@@3HA=00a71ea0
// @ref ?unknown_a71ea4@@3HA=00a71ea4
// @ref ?unknown_games_a3fa64@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa64

int __fastcall Request_To_Join_005bfc40(int game, bool unknown)
{
    if (game < 1) {
        Unknown_005C2C80(unknown_color_7a7360, StringTable::Load_String("TXT_MUST_SELECT_GAME", 0, "D:\\Ra2\\netdlg2.cpp", 3423));
        Voc_Play(Rules->SystemError, 1.0f, 0x2000, 0);
        return 0;
    }
    if (unknown_games_a3fa64.Count() <= 1 || game > unknown_games_a3fa64.Count()) {
        Unknown_005C2C80(unknown_color_7a7360, StringTable::Load_String("TXT_NOTHING_TO_JOIN", 0, "D:\\Ra2\\netdlg2.cpp", 3430));
        Voc_Play(Rules->SystemError, 1.0f, 0x2000, 0);
        return 0;
    }
    if (strlen(unknown_name_a3d3a0) == 0) {
        Unknown_005C2C80(unknown_color_7a7360, StringTable::Load_String("TXT_NAME_ERROR", 0, "D:\\Ra2\\netdlg2.cpp", 3438));
        Voc_Play(Rules->SystemError, 1.0f, 0x2000, 0);
        return 0;
    }
    if (strcmp(unknown_name_a3d3a0, Unknown_006FA120(unknown_lobby_texts_a72d0c[0])) == 0
        || strcmp(unknown_name_a3d3a0, Unknown_006FA120(unknown_lobby_texts_a72d0c[1])) == 0
        || strcmp(unknown_name_a3d3a0, Unknown_006FA120(unknown_lobby_texts_a72d0c[2])) == 0
        || strcmp(unknown_name_a3d3a0, Unknown_006FA120(unknown_lobby_texts_a72d0c[3])) == 0
        || strcmp(unknown_name_a3d3a0, Unknown_006FA120(unknown_lobby_texts_a72d0c[4])) == 0
        || strcmp(unknown_name_a3d3a0, Unknown_006FA120(unknown_lobby_texts_a72d0c[5])) == 0
        || strcmp(unknown_name_a3d3a0, Unknown_006FA120(unknown_lobby_texts_a72d0c[6])) == 0
        || Unknown_Is_Lobby_Name_005cd2f0(unknown_name_a3d3a0)) {
        Unknown_005C2C80(unknown_color_7a7360, StringTable::Load_String("ERROR:NameIsReservedWord", 0, "D:\\Ra2\\netdlg2.cpp", 3453));
        Voc_Play(Rules->SystemError, 1.0f, 0x2000, 0);
        return 0;
    }
    if (!unknown_games_a3fa64[game]->Game.IsOpen) {
        Unknown_005C2C80(unknown_color_7a7360, StringTable::Load_String("TXT_GAME_IS_CLOSED", 0, "D:\\Ra2\\netdlg2.cpp", 3461));
        Voc_Play(Rules->SystemError, 1.0f, 0x2000, 0);
        return 0;
    }
    UnknownGlobalPacket packet;
    memset(&packet, 0, sizeof(packet));
    packet.Command = 6;
    strcpy(packet.Name, unknown_name_a3d3a0);
    strcpy(packet.unknown_18, unknown_a71bc4);
    packet.Join.unknown_2f = unknown_session_a3d298.Value_0124_006729f0();
    packet.Join.unknown_33 = unknown_session_a3d298.Value_011c_00672a10();
    packet.Join.unknown_3b = version_object_00a40c88.Unknown_007131b0();
    packet.Join.unknown_3f = version_object_00a40c88.Unknown_007131c0();
    packet.Join.unknown_43 = unknown_a71e9c;
    packet.Join.unknown_4b = unknown_a71ea0;
    packet.Join.unknown_47 = unknown_a71ea4;
    packet.Join.unknown_4f = Unknown_00737af0();
    packet.Join.unknown_57 = unknown;
    unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_games_a3fa64[game]->Address, 0, 0);
    return 1;
}
