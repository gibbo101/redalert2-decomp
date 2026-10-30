#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
extern "C" int __cdecl _strnicmp(char const *,char const *,unsigned int);
extern HANDLE wol_wait_events_b264f8[18];
extern int unknown_b2ac2c,unknown_b2ab88;
extern long unknown_b2a8a4;
// @ref ?unknown_b2ac2c@@3HA=00b2ac2c
// @ref ?unknown_b2ab88@@3HA=00b2ab88
// @ref ?unknown_b2a8a4@@3JA=00b2a8a4
extern char match_start_buffer_00b2658c[];
// @ref __strnicmp=007858d0
// @ref ?wol_wait_events_b264f8@@3PAPAXA=00b264f8
// @ref ?match_start_buffer_00b2658c@@3PADA=00b2658c
extern char match_fail_prefix_008001f4[];
// @ref ?match_fail_prefix_008001f4@@3PADA=008001f4
extern char match_fail_label_008001e4[];
// @ref ?match_fail_label_008001e4@@3PADA=008001e4
extern char match_ping_prefix_008001d8[];
// @ref ?match_ping_prefix_008001d8@@3PADA=008001d8
extern char match_ping_label_008001c4[];
// @ref ?match_ping_label_008001c4@@3PADA=008001c4
extern char match_rank_prefix_008001b8[];
// @ref ?match_rank_prefix_008001b8@@3PADA=008001b8
extern char match_rank_label_008001a4[];
// @ref ?match_rank_label_008001a4@@3PADA=008001a4
extern char match_side_prefix_00800198[];
// @ref ?match_side_prefix_00800198@@3PADA=00800198
extern char match_side_label_00800180[];
// @ref ?match_side_label_00800180@@3PADA=00800180
extern char match_exit_prefix_00800178[];
// @ref ?match_exit_prefix_00800178@@3PADA=00800178
extern char match_exit_label_007ffd8c[];
// @ref ?match_exit_label_007ffd8c@@3PADA=007ffd8c
extern char match_working_prefix_00800170[];
// @ref ?match_working_prefix_00800170@@3PADA=00800170
extern char match_working_label_00800158[];
// @ref ?match_working_label_00800158@@3PADA=00800158
extern char match_info_prefix_00800150[];
// @ref ?match_info_prefix_00800150@@3PADA=00800150
extern char match_pool_prefix_00800148[];
// @ref ?match_pool_prefix_00800148@@3PADA=00800148
extern char match_pool_label_00800130[];
// @ref ?match_pool_label_00800130@@3PADA=00800130
extern char match_start_prefix_00800128[];
// @ref ?match_start_prefix_00800128@@3PADA=00800128
extern char match_ack1_00800124[];
// @ref ?match_ack1_00800124@@3PADA=00800124
extern char match_ack2_0080011c[];
// @ref ?match_ack2_0080011c@@3PADA=0080011c
extern char match_need_prefix_00800114[];
// @ref ?match_need_prefix_00800114@@3PADA=00800114
extern char match_unknown_label_008000f4[];
// @ref ?match_unknown_label_008000f4@@3PADA=008000f4
extern char match_debug_format_007d5a34[];
// @ref ?match_debug_format_007d5a34@@3PADA=007d5a34
extern char wol_source_file_007fd62c[];
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
void __fastcall Handle_Matchmaking_Command_0075b910(char const *text,char from_server)
{
    if(from_server) {
        if(!_strnicmp(text,match_fail_prefix_008001f4,4)) {
            Unknown_005C2C80(0x40ffff,StringTable::Load_String(match_fail_label_008001e4,0,wol_source_file_007fd62c,0x6753));
            SetEvent(wol_wait_events_b264f8[17]);
            return;
        }
        if(!_strnicmp(text,match_ping_prefix_008001d8,8)) {
            Unknown_005C2C80(0x40ffff,StringTable::Load_String(match_ping_label_008001c4,0,wol_source_file_007fd62c,0x6759));
            SetEvent(wol_wait_events_b264f8[17]);
            return;
        }
        if(!_strnicmp(text,match_rank_prefix_008001b8,8)) {
            Unknown_005C2C80(0x40ffff,StringTable::Load_String(match_rank_label_008001a4,0,wol_source_file_007fd62c,0x675f));
            SetEvent(wol_wait_events_b264f8[17]);
            return;
        }
        if(!_strnicmp(text,match_side_prefix_00800198,11)) {
            Unknown_005C2C80(0x40ffff,StringTable::Load_String(match_side_label_00800180,0,wol_source_file_007fd62c,0x6765));
            SetEvent(wol_wait_events_b264f8[17]);
            return;
        }
    }
    if(!_strnicmp(text,match_exit_prefix_00800178,4)) {
        Unknown_005C2C80(0x40ffff,StringTable::Load_String(match_exit_label_007ffd8c,0,wol_source_file_007fd62c,0x676b));
        unknown_chat_a72cfc->unknown_slot09();
        Message_Box_005c3230(StringTable::Load_String(match_exit_label_007ffd8c,0,wol_source_file_007fd62c,0x676e),0,(bool (*)())Unknown_0073c120,false);
        SetEvent(wol_wait_events_b264f8[0]);
        return;
    }
    if(!_strnicmp(text,match_working_prefix_00800170,7)) {
        if(unknown_b26898==4) {
            unknown_b2ac2c=0;
            unknown_b26898=5;
            unknown_b2ab88=180;
            unknown_b2a8a4=time(0);
        }
        Unknown_005C2C80(unknown_color_7a7360,StringTable::Load_String(match_working_label_00800158,0,wol_source_file_007fd62c,0x677a));
        return;
    }
    if(!_strnicmp(text,match_info_prefix_00800150,5)) {
        Unknown_005C2C80(0xff8080,Unknown_006FA180(text+5));
        return;
    }
    if(!_strnicmp(text,match_pool_prefix_00800148,5)) {
        Unknown_005C2C80(0xff8080,StringTable::Load_String(match_pool_label_00800130,0,wol_source_file_007fd62c,0x6784),text+5);
        return;
    }
    if(from_server && !_strnicmp(text,match_start_prefix_00800128,6)) {
        strncpy(match_start_buffer_00b2658c,text+6,255);
        Debug_Printf(match_debug_format_007d5a34,match_start_buffer_00b2658c);
        SetEvent(wol_wait_events_b264f8[16]);
        return;
    }
    if(_stricmp(text,match_ack1_00800124) && _stricmp(text,match_ack2_0080011c)) {
        if(!_strnicmp(text,match_need_prefix_00800114,5)) {
            Debug_Printf(match_debug_format_007d5a34,text);
            return;
        }
        if(from_server) Unknown_005C2C80(0x40ffff,StringTable::Load_String(match_unknown_label_008000f4,0,wol_source_file_007fd62c,0x67a5));
    }
}
