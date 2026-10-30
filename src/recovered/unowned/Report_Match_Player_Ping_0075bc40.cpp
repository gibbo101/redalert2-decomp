#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
extern Wstring unknown_b2997c;
extern char wol_source_file_007fd62c[];
extern char match_found_label_00800234[];
extern char match_ping_label_0080021c[];
extern char match_no_ping_label_008001fc[];
// @ref ?unknown_ladder_b2ab98@@3VWolLadderCache@@A=00b2ab98
// @ref ?unknown_b2997c@@3VWstring@@A=00b2997c
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ?match_found_label_00800234@@3PADA=00800234
// @ref ?match_ping_label_0080021c@@3PADA=0080021c
// @ref ?match_no_ping_label_008001fc@@3PADA=008001fc
void __fastcall Report_Match_Player_Ping_0075bc40()
{
    Unknown_005C2C80(0xc0ffff,StringTable::Load_String(match_found_label_00800234,0,wol_source_file_007fd62c,0x67ba),unknown_b2997c.Buffer);
    Wstring lower=unknown_b2997c.As_Lower();
    // The original performs this lookup before resolving the player; its result is unused.
    WOL::Ladder *ladder;
    unknown_ladder_b2ab98.Get_Pointer(lower,&ladder);
    int index=unknown_users_b2a728.Find_Name(unknown_b2997c.Get());
    if(index==-1) {
        Unknown_005C2C80(0xc0ffff,StringTable::Load_String(match_no_ping_label_008001fc,0,wol_source_file_007fd62c,0x67c7));
        return;
    }
    {
        WOL::User user;
        memset(&user,0,sizeof(user));
        unknown_users_b2a728.Get_Copy(user,index);
        if(!user.unknown_18) {
            Unknown_005C2C80(0xc0ffff,StringTable::Load_String(match_no_ping_label_008001fc,0,wol_source_file_007fd62c,0x67ce));
            return;
        }
        int ping=-1;
        unknown_ladder_client_a72d00->Get_Average_Ping(user.unknown_18,&ping);
        if(ping!=-1) {
            Unknown_005C2C80(0xc0ffff,StringTable::Load_String(match_ping_label_0080021c,0,wol_source_file_007fd62c,0x67d4),ping);
        } else {
            Unknown_005C2C80(0xc0ffff,StringTable::Load_String(match_no_ping_label_008001fc,0,wol_source_file_007fd62c,0x67d6));
        }
    }
}
