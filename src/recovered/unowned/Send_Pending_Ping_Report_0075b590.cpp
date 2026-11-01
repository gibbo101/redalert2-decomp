// @ref ?Shrink@?$WolArrayList@VWstring@@@@QAE_NXZ=00767b20
// @ref ??_GWstring@@QAEPAXI@Z=007667c0
// @ref ?ping_report_title_8000ec@@3PADA=008000ec
// @ref ?ping_report_pending_8000c0@@3PADA=008000c0
// @ref ?ping_report_removed_80009c@@3PADA=0080009c
// @ref ?ping_report_average_800088@@3PADA=00800088
// @ref ?ping_report_terminator_7d27e4@@3PADA=007d27e4
// @ref ?ping_report_separator_7ce9c0@@3PADA=007ce9c0
// @ref ?ping_report_error_80006c@@3PADA=0080006c
// @ref ?ping_report_sent_800054@@3PADA=00800054
#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
extern WolStringArray unknown_strings_b29828;
extern char pending_ping_missing_007fffb0[];
extern char pending_ping_no_ip_007fffc8[];
extern char ping_report_title_8000ec[];
extern char ping_report_pending_8000c0[];
extern char ping_report_removed_80009c[];
extern char ping_report_average_800088[];
extern char ping_report_error_80006c[];
extern char ping_report_sent_800054[];
extern char ping_report_separator_7ce9c0[];
extern char ping_report_terminator_7d27e4[];
void __fastcall Send_Pending_Ping_Report_0075b590()
{
    int sent=0;
    WOL::User user;
    memset(&user,0,sizeof(user));
    if(unknown_b2ac40) return;
    Wstring packet(ping_report_title_8000ec);
    Debug_Printf(ping_report_pending_8000c0,unknown_strings_b29828.Count);
    while(unknown_strings_b29828.Count) {
        Wstring name;
        unknown_strings_b29828.Remove_Tail(name);
        Debug_Printf(ping_report_removed_80009c,name.Get());
        int index=unknown_users_b2a728.Find_Name(name.Get());
        if(index==-1) Debug_Printf(pending_ping_missing_007fffb0,name.Get());
        else {
            unknown_users_b2a728.Get_Copy(user,index);
            if(!user.unknown_18) Debug_Printf(pending_ping_no_ip_007fffc8,name.Get());
            else {
                int average=-1;
                unknown_ladder_client_a72d00->Get_Average_Ping(user.unknown_18,&average);
                if(average!=-1) {
                    Debug_Printf(ping_report_average_800088,name.Get(),average);
                    packet += name+Wstring(ping_report_separator_7ce9c0)+Wstring_From_Integer(average)+Wstring(ping_report_terminator_7d27e4);
                    ++sent;
                } else Debug_Printf(ping_report_error_80006c,name.Get());
            }
        }
    }
    unknown_b26568=0;
    if(0<sent) {
        WOL::User *host=Unknown_0074DA60();
        if(host) {
            unknown_chat_a72cfc->unknown_slot12(host,packet.Get());
            Debug_Printf(ping_report_sent_800054,packet.Get());
        }
    }
}
