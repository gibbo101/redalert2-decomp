#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/crt_string.hpp"
bool __fastcall Unknown_005c9320(NodeNameType const *entry);
bool __fastcall Unknown_005c9370(NodeNameType const *entry);
void __fastcall Unknown_0073cff0(char *buffer);
extern char channel_mode_prefix_007feae4[],channel_limit_option_007feaec[],channel_command_eol_007d7cec[];
// @ref ?Unknown_005c9320@@YI_NPBUNodeNameType@@@Z=005c9320
// @ref ?Unknown_005c9370@@YI_NPBUNodeNameType@@@Z=005c9370
// @ref ?Unknown_0073cff0@@YIXPAD@Z=0073cff0
// @ref ?channel_mode_prefix_007feae4@@3PADA=007feae4
// @ref ?channel_limit_option_007feaec@@3PADA=007feaec
// @ref ?channel_command_eol_007d7cec@@3PADA=007d7cec
void __fastcall Update_Channel_Player_Limit_00749f20()
{
    int limit=Scenario_Slot_Limit_005c65a0(unknown_session_a3d2b4);
    if(unknown_a72c68==1) ++limit;
    int fixed_slots=0;
    int open_slots=0;
    int player_slots=0;
    int i=1;
    for(;i<limit;++i) {
        NodeNameType *entry=unknown_player_slots_a3fa98[i];
        if(entry!=unknown_open_entry_a72d2c && entry!=unknown_player_a72d44) {
            if(Unknown_005c9320(entry)) ++fixed_slots;
            else if(Unknown_005c9370(entry)) ++player_slots;
        } else ++open_slots;
    }
    for(;i<8;++i) {
        NodeNameType *entry=unknown_player_slots_a3fa98[i];
        if(entry==unknown_player_a72d44) ++open_slots;
        else if(Unknown_005c9320(entry)) ++fixed_slots;
    }
    if(unknown_chat_a72cfc) {
        int capacity=open_slots+fixed_slots+1;
        Wstring command=Wstring(channel_mode_prefix_007feae4)+Wstring(unknown_game_channel_b299c0.name)+Wstring(channel_limit_option_007feaec)+Wstring_From_Integer(capacity)+Wstring(channel_command_eol_007d7cec);
        unknown_chat_a72cfc->unknown_slot39(command.Get());
        char info[80];
        memset(info,0,sizeof(info));
        Unknown_0073cff0(info);
        info[40]=0;
        unknown_chat_a72cfc->unknown_slot42(info);
        unknown_chat_a72cfc->unknown_slot63(1,capacity+player_slots);
    }
}
