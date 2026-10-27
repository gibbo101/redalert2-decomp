#include "shared/coop_campaign.hpp"
#include "shared/mplayer_score_type.hpp"
bool CoopCampaignClass::Add_Score_0048f730(int index, int time, MPlayerScoreType first, MPlayerScoreType second)
{
    if(index>=0 && index<MapCount) {
        Kills[0]+=first.Kills;
        Kills[1]+=second.Kills;
        Built[0]+=first.Built;
        Built[1]+=second.Built;
        Lost[0]+=first.Lost;
        Lost[1]+=second.Lost;
        Score[0]+=first.Score;
        Score[1]+=second.Score;
        Time=time;
        CurrentMap=index;
        return true;
    }
    return false;
}
