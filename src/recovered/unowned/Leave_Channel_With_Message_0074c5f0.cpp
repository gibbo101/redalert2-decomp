#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/string_table.hpp"
extern char leave_channel_label_007fde60[],observer_leave_label_007e6cdc[];
extern char wol_source_file_007fd62c[];
bool connection_wait_callback_0073c120();
void __fastcall Close_Online_Dialog_007357e0(HWND,int);
// @ref ?leave_channel_label_007fde60@@3PADA=007fde60
// @ref ?observer_leave_label_007e6cdc@@3PADA=007e6cdc
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ?connection_wait_callback_0073c120@@YA_NXZ=0073c120
// @ref ?Close_Online_Dialog_007357e0@@YIXPAUHWND__@@H@Z=007357e0
void __fastcall Leave_Channel_With_Message_0074c5f0(HWND dialog)
{
    if(dialog) {
        if(unknown_a72c68==0) {
            Message_Box_005c3230(StringTable::Load_String(leave_channel_label_007fde60,0,wol_source_file_007fd62c,0x3c0f),0,connection_wait_callback_0073c120,false);
        } else {
            Message_Box_005c3230(StringTable::Load_String(observer_leave_label_007e6cdc,0,wol_source_file_007fd62c,0x3c11),0,connection_wait_callback_0073c120,false);
        }
        if(unknown_chat_a72cfc->unknown_slot09()<0) Close_Online_Dialog_007357e0(dialog,2);
    }
}
