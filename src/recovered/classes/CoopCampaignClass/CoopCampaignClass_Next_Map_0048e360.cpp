#include "shared/coop_campaign.hpp"
#include "shared/mplayer_score_type.hpp"
#include "shared/id_source.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/crt_string.hpp"
void __fastcall Collect_Coop_Player_Score_0048e210(MPlayerScoreType &output, bool skip_first);
char *__fastcall Unknown_006FA120(unsigned short const *string);
extern "C" int __cdecl sprintf(char *destination, char const *format, ...);
extern char const next_map_log_007d4f38[];
extern char const local_player_log_007d4f24[];
extern char const assume_local_player_log_007d4f08[];
extern char const game_time_log_007d4ed4[];
extern char const time_format_007d4ef8[];
// @ref ?Collect_Coop_Player_Score_0048e210@@YIXAAVMPlayerScoreType@@_N@Z=0048e210
// @ref ?Unknown_006FA120@@YIPADPBG@Z=006fa120
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref _sprintf=007820f4
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?next_map_log_007d4f38@@3QBDB=007d4f38
// @ref ?local_player_log_007d4f24@@3QBDB=007d4f24
// @ref ?assume_local_player_log_007d4f08@@3QBDB=007d4f08
// @ref ?game_time_log_007d4ed4@@3QBDB=007d4ed4
// @ref ?time_format_007d4ef8@@3QBDB=007d4ef8
inline void Format_Time(int seconds, char *buffer)
{
    if(buffer) {
        if(seconds/3600>99) seconds=359999;
        int hours=seconds/3600;
        seconds-=hours*3600;
        int minutes=seconds/60;
        seconds-=minutes*60;
        sprintf(buffer,time_format_007d4ef8,hours,minutes,seconds);
    }
}
bool CoopCampaignClass::Next_Map_0048e360()
{
    if(!Initialized) return false;
    Debug_Printf(next_map_log_007d4f38);
    MPlayerScoreType first;
    Collect_Coop_Player_Score_0048e210(first,false);
    MPlayerScoreType second;
    Collect_Coop_Player_Score_0048e210(second,true);
    if(strcmp(FirstName,Unknown_006FA120(first.Name))==0) {
        Debug_Printf(local_player_log_007d4f24,Unknown_006FA120(first.Name));
        Kills[0]+=first.Kills; Kills[1]+=second.Kills;
        Built[0]+=first.Built; Built[1]+=second.Built;
        Lost[0]+=first.Lost; Lost[1]+=second.Lost;
        Score[0]+=first.Score; Score[1]+=second.Score;
    } else {
        Debug_Printf(assume_local_player_log_007d4f08,Unknown_006FA120(second.Name));
        Kills[1]+=first.Kills; Kills[0]+=second.Kills;
        Built[1]+=first.Built; Built[0]+=second.Built;
        Lost[1]+=first.Lost; Lost[0]+=second.Lost;
        Score[1]+=first.Score; Score[0]+=second.Score;
    }
    char game_time[256];
    Format_Time(unknown_id_source_a3d290->Elapsed_Time().Time()/60,game_time);
    Time+=unknown_id_source_a3d290->Elapsed_Time().Time();
    char total_time[256];
    Format_Time(Time,total_time);
    Debug_Printf(game_time_log_007d4ed4,game_time,total_time);
    ++CurrentMap;
    return true;
}
