// bool __fastcall Parse_Command_Line(int argc, char *argv[]) -- 0x00515110
// Body 0x00515110-0x0051570A (1531 bytes, nop padding to 0x00515710). TS's Parse_Command_Line with
// RA2's switches (-jabber/-str/-nostr, -noaudio, -record/-play, -DROP=, router and -WIN switches).
#include "shared/special.hpp"
#include "shared/cd.hpp"
#include "shared/cd_file_class.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/ipx_address.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/gscreen.hpp"
#include "shared/dsurface.hpp"
#include "shared/lobby.hpp"
#include "shared/options.hpp"
#include "shared/session_state.hpp"
#include "shared/string_table.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_tokens.hpp"

// @ref ?Obfuscate@@YIJPBD@Z=005d8390
// @ref __putws=0078432e
// @ref __strnicmp=007858d0
// @ref ?Set_Text_Option_006f9fb0@@YIXH@Z=006f9fb0
// @ref ?Set_Text_Option_006f9fe0@@YIXH@Z=006f9fe0
// @ref ?unknown_record_mode_a41664@@3HA=00a41664
// @ref ?unknown_router_b2ac30@@3HA=00b2ac30
// @ref ?unknown_router_a402d0@@3_NA=00a402d0
// @ref ?unknown_session_a3f615@@3_NA=00a3f615
// @ref ??_C@_01PJCK@?4?$AA@=007dbe44
// @ref ??_C@_02JDLK@?$CFx?$AA@=007db4b4
// @ref ??_C@_0BA@NANB@D?3?2Ra2?2Init?4CPP?$AA@=007db8e4
// @ref ??_C@_02HEAO@?9X?$AA@=007dbda8
// @ref ??_C@_02IIJL@?9O?$AA@=007dbdac
// @ref ??_C@_02IPJO@?9h?$AA@=007dbe5c
// @ref ??_C@_02KCML@?1h?$AA@=007dbe58
// @ref ??_C@_02NGML@?9?$DP?$AA@=007dbe60
// @ref ??_C@_02PLJO@?1?$DP?$AA@=007dbe64
// @ref ??_C@_03FGOK@?9CD?$AA@=007dbe54
// @ref ??_C@_03GFJP@?916?$AA@=007dbdb8
// @ref ??_C@_04CNDI@?9WIN?$AA@=007dbdb0
// @ref ??_C@_04GEGM@?9str?$AA@=007dbe8c
// @ref ??_C@_04OKBC@?9480?$AA@=007dbdbc
// @ref ??_C@_05FIGE@?9play?$AA@=007dbe68
// @ref ??_C@_06GFOL@?9?$CFdX?$CFd?$AA@=007dbdc4
// @ref ??_C@_06GMGD@?9nostr?$AA@=007dbe84
// @ref ??_C@_06HMHB@SOCKET?$AA@=007dbe34
// @ref ??_C@_06NMHF@?9DROP?$DN?$AA@=007dbe20
// @ref ??_C@_07CKPF@?9jabber?$AA@=007dbe94
// @ref ??_C@_07EOKL@?9SOCKET?$AA@=007dbe3c
// @ref ??_C@_07FDJO@?9DLINK1?$AA@=007dbe08
// @ref ??_C@_07KPDG@?9record?$AA@=007dbe70
// @ref ??_C@_08BJJN@?9STEALTH?$AA@=007dbde4
// @ref ??_C@_08ECCE@?9noaudio?$AA@=007dbe78
// @ref ??_C@_08FOIG@?9DESTNET?$AA@=007dbe48
// @ref ??_C@_08GLMP@?9MPDEBUG?$AA@=007dbe28
// @ref ??_C@_08ODNK@?9ATTRACT?$AA@=007dbdcc
// @ref ??_C@_08OOHL@?9NETGEAR?$AA@=007dbdfc
// @ref ??_C@_09LLPH@?9MESSAGES?$AA@=007dbdd8
// @ref ??_C@_09OBOH@?9NOROUTER?$AA@=007dbdf0
// @ref ??_C@_0BD@BACE@TXT_OPTION_HELP_04?$AA@=007dbd4c
// @ref ??_C@_0BD@BAOP@TXT_OPTION_HELP_01?$AA@=007dbd88
// @ref ??_C@_0BD@EFAK@TXT_OPTION_HELP_06?$AA@=007dbd24
// @ref ??_C@_0BD@EFMB@TXT_OPTION_HELP_03?$AA@=007dbd60
// @ref ??_C@_0BD@LKLD@TXT_OPTION_HELP_05?$AA@=007dbd38
// @ref ??_C@_0BD@OPFG@TXT_OPTION_HELP_02?$AA@=007dbd74
// @ref ??_C@_0M@PKNM@TXT_INVALID?$AA@=007dbd9c
// @ref ??_C@_0O@BLIL@?9SPEEDCONTROL?$AA@=007dbe10

extern "C" char *__cdecl _strupr(char *string);
extern "C" char *__cdecl strstr(char const *string, char const *find);
extern "C" int __cdecl sscanf(char const *buffer, char const *format, ...);
extern "C" int __cdecl atoi(char const *string);
extern "C" int __cdecl isdigit(int character);
extern "C" int __cdecl toupper(int character);
extern "C" int __cdecl _putws(wchar_t const *string);

long __fastcall Obfuscate(char const *string);             // 0x005D8390
void __fastcall Set_Text_Option_006f9fb0(int value);        // 0x006F9FB0 (-jabber)
void __fastcall Set_Text_Option_006f9fe0(int value);        // 0x006F9FE0 (-str / -nostr)
extern int unknown_audio_7f4cc8;                // 0x007F4CC8 cleared by -noaudio
extern int unknown_record_mode_a41664;          // 0x00A41664 1 = -record, 2 = -play
extern bool unknown_extra_sync_info_ab62e8;     // 0x00AB62E8 set by -MPDEBUG
extern int unknown_router_b2ac30;               // 0x00B2AC30 1 = -DLINK1, 2 = -NETGEAR
extern bool unknown_router_a402d0;              // 0x00A402D0 cleared by -NOROUTER
extern bool unknown_session_a3f615;             // 0x00A3F615 cleared by -MESSAGES (TS's Session.NetProtect)
extern bool unknown_hicolor_7ce008;             // 0x007CE008 set by -16 (TS's HicolorFlag)
extern char unknown_flag_a40d0c;                // 0x00A40D0C set by -XQ (TS's Debug_Quiet)

#define PARM_INSTALL 0xD95C68A2

bool __fastcall Parse_Command_Line(int argc, char *argv[])
{
    unknown_special_a40920.Init();

    unknown_a40d13 = false;

    for (int index = 1; index < argc; index++) {
        char *string;
        string = _strupr(argv[index]);

        if (_stricmp("-jabber", string) == 0) {
            Set_Text_Option_006f9fb0(1);
        } else if (_stricmp("-str", string) == 0) {
            Set_Text_Option_006f9fe0(1);
        } else if (_stricmp("-nostr", string) == 0) {
            Set_Text_Option_006f9fe0(0);
        } else if (_stricmp("-noaudio", string) == 0) {
            unknown_audio_7f4cc8 = 0;
        } else if (_stricmp("-record", string) == 0) {
            unknown_record_mode_a41664 = 1;
        } else if (_stricmp("-play", string) == 0) {
            unknown_record_mode_a41664 = 2;
        } else {
            if (_stricmp("/?", string) == 0 || _stricmp("-?", string) == 0 || _stricmp("-h", string) == 0 || _stricmp("/h", string) == 0) {
                _putws(StringTable::Load_String("TXT_OPTION_HELP_01", 0, "D:\\Ra2\\Init.CPP", 0xD0E));
                _putws(StringTable::Load_String("TXT_OPTION_HELP_02", 0, "D:\\Ra2\\Init.CPP", 0xD0F));
                _putws(StringTable::Load_String("TXT_OPTION_HELP_03", 0, "D:\\Ra2\\Init.CPP", 0xD10));
                _putws(StringTable::Load_String("TXT_OPTION_HELP_04", 0, "D:\\Ra2\\Init.CPP", 0xD11));
                _putws(StringTable::Load_String("TXT_OPTION_HELP_05", 0, "D:\\Ra2\\Init.CPP", 0xD12));
                _putws(StringTable::Load_String("TXT_OPTION_HELP_06", 0, "D:\\Ra2\\Init.CPP", 0xD13));
                return false;
            }

            bool processed = true;
            long ob = Obfuscate(string);
            switch (ob) {
                case PARM_INSTALL:
                    unknown_special_a40920.IsFromInstall = true;
                    break;

                default:
                    processed = false;
                    break;
            }
            if (processed) continue;

            if (strstr(string, "-CD")) {
                CD::IsLocal = true;
                CDFileClass::Set_Search_Drives(&string[3]);
                continue;
            }

            if (strstr(string, "-DESTNET")) {
                NetNumType net;
                NetNodeType node;

                int i = 0;
                char *p = strtok(string + 8, ".");
                while (p) {
                    int x;
                    sscanf(p, "%x", &x);
                    if (i < 4) {
                        net[i] = (char)x;
                    } else {
                        node[i - 4] = (char)x;
                    }
                    i++;
                    p = strtok(0, ".");
                }

                if (i >= 4) {
                    unknown_dest_net_set_a3f604 = 1;
                    memset(node, 0xFF, 6);
                    unknown_dest_net_a3f608 = IPXAddressClass(net, node, 0);
                }
                continue;
            }

            if (strstr(string, "-SOCKET")) {
                unsigned short socket;
                socket = (unsigned short)(atoi(string + strlen("SOCKET")));
                socket += (unsigned short)0x4000;
                if (socket >= 0x4000 && socket < 0x8000) {
                    unknown_ipx_manager_a40978.Set_Socket(socket);
                }
                continue;
            }

            WinsockInterfaceClass::unknown_76b9e0(0);

            if (strstr(string, "-MPDEBUG")) {
                unknown_extra_sync_info_ab62e8 = true;
                unknown_flag_a3d8c4 = true;
            }

            if (strstr(string, "-DROP=")) {
                WinsockInterfaceClass::unknown_76b9e0((unsigned short)atoi(string + strlen("-DROP=")));
                continue;
            }

            if (strstr(string, "-SPEEDCONTROL")) {
                unknown_flag_a40d84 = true;
            }
            if (strstr(string, "-DLINK1")) {
                unknown_router_b2ac30 = 1;
            }
            if (strstr(string, "-NETGEAR")) {
                unknown_router_b2ac30 = 2;
            }
            if (strstr(string, "-NOROUTER")) {
                unknown_router_a402d0 = false;
            }

            if (strstr(string, "-STEALTH")) {
                unknown_session_a3f614 = true;
                continue;
            }

            if (strstr(string, "-MESSAGES")) {
                unknown_session_a3f615 = false;
                continue;
            }

            if (strstr(string, "-ATTRACT")) {
                unknown_session_a3d298.Attract = true;
                continue;
            }

            if (isdigit(string[1])) {
                sscanf(string, "-%dX%d", &Options.ScreenWidth, &Options.ScreenHeight);
                continue;
            }

            if (strcmp(string, "-480") == 0) {
                Options.ScreenHeight = 480;
                continue;
            }

            if (strcmp(string, "-16") == 0) {
                unknown_hicolor_7ce008 = true;
                continue;
            }

            if (_stricmp(string, "-WIN") == 0) {
                unknown_flag_851cb0 = true;
                continue;
            }

            if (_strnicmp(string, "-X", strlen("-O")) == 0) {
                string += strlen("-X");
                while (*string) {
                    char code = *string++;
                    switch (toupper(code)) {
                        case 'Q':
                            unknown_flag_a40d0c = true;
                            break;

                        default:
                            _putws(StringTable::Load_String("TXT_INVALID", 0, "D:\\Ra2\\Init.CPP", 0xE4C));
                            return false;
                    }
                }
                continue;
            }
        }
    }
    return true;
}
