// Complete original114B+14NOP; full original body mapped before source.
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
extern char unknown_scenario_a3d8f0[];
extern char user_options_format_7fd6c4[];
int __fastcall Channel_Version_00737af0();
namespace seed_005c9400 { int FUN_005c9400(); }
// @ref ?unknown_scenario_a3d8f0@@3PADA=00a3d8f0
// @ref ?user_options_format_7fd6c4@@3PADA=007fd6c4
// @ref ?Channel_Version_00737af0@@YIHXZ=00737af0
// @ref ?FUN_005c9400@seed_005c9400@@YAHXZ=005c9400
void __fastcall Format_User_Options_0073cff0(char *text)
{
    int country_zero_count=0;
    int country_one_count=0;
    for(int index=0;index<(int)unknown_game_channel_b299c0.currentUsers;++index) {
        int country=unknown_player_b29cf0[index].unknown_18;
        if(country==0) ++country_zero_count;
        else if(country==1) ++country_one_count;
    }
    int free_sides=0;
    if(country_one_count<(int)unknown_game_channel_b299c0.maxUsers/2) free_sides=2;
    if(country_zero_count<(int)unknown_game_channel_b299c0.maxUsers/2) ++free_sides;
    unsigned int check=Unknown_0073cfd0();
    sprintf(text,user_options_format_7fd6c4,Channel_Version_00737af0(),check,seed_005c9400::FUN_005c9400(),Unknown_005c94b0(),!No_Observer_Slot_005c9490(),unknown_scenario_a3d8f0);
}
