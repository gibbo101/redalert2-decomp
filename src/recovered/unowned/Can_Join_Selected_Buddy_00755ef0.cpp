#include "shared/wol_sink.hpp"
bool __fastcall Can_Join_Channel_00755cd0(WOL::Channel const *,bool,bool);
// @ref ?Can_Join_Channel_00755cd0@@YI_NPBUChannel@WOL@@_N1@Z=00755cd0
bool __fastcall Can_Join_Selected_Buddy_00755ef0()
{
    if(unknown_wstring_b29cd4.Length()==0) return false;
    unsigned int state=0;
    unknown_names_b29848.Get_Value(unknown_wstring_b29cd4,state);
    if(state==4) return true;
    if(state!=5) return false;
    WOL::Channel channel;
    if(!unknown_channels_b29478.Get_Value(unknown_wstring_b29cd4,channel)) return false;
    Wstring game_name(channel.channel_name);
    WOL::Channel game;
    if(!unknown_games_b29990.Find_Name(game_name,game)) return false;
    return Can_Join_Channel_00755cd0(&game,false,unknown_a72c68!=0);
}
