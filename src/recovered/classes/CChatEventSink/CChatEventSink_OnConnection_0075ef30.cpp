#include "shared/wol_sink.hpp"
extern "C" long __cdecl atol(char const *text);
extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);
HRESULT __stdcall CChatEventSink::OnConnection(HRESULT result, char const *motd)
{
    unknown_connection_result_b2ac10 = result;
    if (result < 0) unknown_b2abd8 = true;
    switch (result) {
    case (HRESULT)0x80040064:
        wcscpy(unknown_connection_error_b2a8ec, StringTable::Load_String("TXT_LOGIN_USED", 0, "D:\\Ra2\\wonline.cpp", 0x11ba));
        SetEvent(unknown_b264f8);
        break;
    case (HRESULT)0x80040065:
        wcscpy(unknown_connection_error_b2a8ec, StringTable::Load_String("TXT_BADPASS", 0, "D:\\Ra2\\wonline.cpp", 0x11bf));
        SetEvent(unknown_b264f8);
        break;
    case (HRESULT)0x80040072:
        wcscpy(unknown_connection_error_b2a8ec, StringTable::Load_String("TXT_BANNED", 0, "D:\\Ra2\\wonline.cpp", 0x11c4));
        SetEvent(unknown_b264f8);
        break;
    case (HRESULT)0x80040074:
        wcscpy(unknown_connection_error_b2a8ec, StringTable::Load_String("TXT_DISABLED", 0, "D:\\Ra2\\wonline.cpp", 0x11ca));
        SetEvent(unknown_b264f8);
        break;
    case (HRESULT)0x80040075:
        wcscpy(unknown_connection_error_b2a8ec, StringTable::Load_String("TXT_BANNED", 0, "D:\\Ra2\\wonline.cpp", 0x11cf));
        SetEvent(unknown_b264f8);
        break;
    case (HRESULT)0x80040076:
        wcscpy(unknown_connection_error_b2a8ec, StringTable::Load_String("TXT_SERIALDUP", 0, "D:\\Ra2\\wonline.cpp", 0x11d4));
        SetEvent(unknown_b264f8);
        break;
    case (HRESULT)0x80040077:
        wcscpy(unknown_connection_error_b2a8ec, StringTable::Load_String("TXT_SERIALUNKNOWN", 0, "D:\\Ra2\\wonline.cpp", 0x11d9));
        SetEvent(unknown_b264f8);
        break;
    case (HRESULT)0x80040078:
        wcscpy(unknown_connection_error_b2a8ec, StringTable::Load_String("TXT_SKUSERIALMISMATCH", 0, "D:\\Ra2\\wonline.cpp", 0x11de));
        SetEvent(unknown_b264f8);
        break;
    default:
        wcscpy(unknown_connection_error_b2a8ec, StringTable::Load_String("TXT_CANT_CONNECT", 0, "D:\\Ra2\\wonline.cpp", 0x11e4));
        SetEvent(unknown_b264f8);
        break;
    case S_OK:
        if (!unknown_icons_b2acc4) {
            char const *types;
            unknown_chat_a72cfc->Game_Types(&types);
            char *copy = new char[strlen(types) + 32];
            strcpy(copy, types);
            strcat(copy, ",-1,0,18");
            char *token = strtok(copy, ",");
            while (token) {
                long id = atol(token);
                int width, height;
                void *bitmap, *palette;
                unknown_chat_a72cfc->Game_Icon(id, unknown_icon_format_7fd304, &bitmap, &palette, &width, &height);
                char file[64];
                sprintf(file, "gt%d.bmp", id);
                unknown_bitmap_writer_a76378.Write_0068c040(file, bitmap, palette, 2);
                token = strtok(0, ",");
            }
            delete [] copy;
            unknown_icons_b2acc4 = 1;
        }
        if (unknown_7fd2fc) unknown_motd_b26954 = motd;
        else unknown_motd_b26954.Release();
        unknown_b2abda = false;
        unknown_b2abe8 = 0;
        memset(&unknown_channel_b299c0, 0, sizeof(unknown_channel_b299c0));
        memset(&unknown_pending_channel_b26a60, 0, sizeof(unknown_pending_channel_b26a60));
        SetEvent(unknown_b26500);
        Find_Local_Address_0074fcb0(&unknown_address_a3fbc8);
        break;
    }
    return S_OK;
}
// @ref ?unknown_bitmap_writer_a76378=00a76378
// @ref ?Write_0068c040@UnknownBitmapWriter@@=0068c040
// @ref ?Find_Local_Address_0074fcb0=0074fcb0
// @ref ?unknown_pending_channel_b26a60=00b26a60
// @ref ?unknown_connection_result_b2ac10=00b2ac10
// @ref ?unknown_b2abd8=00b2abd8
// @ref ?unknown_b2abda=00b2abda
// @ref ?unknown_7fd2fc=007fd2fc
// @ref ?unknown_icons_b2acc4=00b2acc4
// @ref ?unknown_icon_format_7fd304=007fd304
// @ref ?unknown_motd_b26954=00b26954
// @ref ?unknown_b26500=00b26500
// @ref ?unknown_connection_error_b2a8ec=00b2a8ec
// @ref ?unknown_chat_a72cfc=00a72cfc
// @ref ?unknown_channel_b299c0=00b299c0
// @ref ?unknown_b2abe8=00b2abe8
// @ref ?unknown_b264f8=00b264f8
// @ref _wcscpy=00783689
// @ref ??_C@_0BD@IJO@D?3?2Ra2?2wonline?4cpp?$AA@=007fd62c
// @ref ??_C@_08MMLO@gt?$CFd?4bmp?$AA@=007fdd14
// @ref ??_C@_08MLFF@?0?91?00?018?$AA@=007fdd20
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_C@_0BB@CFJ@TXT_CANT_CONNECT?$AA@=007fd740
// @ref ??_C@_0BG@FMGJ@TXT_SKUSERIALMISMATCH?$AA@=007fdd2c
// @ref ??_C@_0O@GCCF@TXT_SERIALDUP?$AA@=007fdd44
// @ref ??_C@_0BC@NEOI@TXT_SERIALUNKNOWN?$AA@=007fdd54
// @ref ??_C@_0N@MPNE@TXT_DISABLED?$AA@=007fdd68
// @ref ??_C@_0L@JEGG@TXT_BANNED?$AA@=007fdd78
// @ref ??_C@_0M@OAG@TXT_BADPASS?$AA@=007fdd84
// @ref ??_C@_0P@CFNN@TXT_LOGIN_USED?$AA@=007fdd90
// @ref ??_C@_0BD@IJO@D?3?2Ra2?2wonline?4cpp?$AA@=007fd62c
// @ref _atol=00782d72
// @ref ?unknown_address_a3fbc8=00a3fbc8
