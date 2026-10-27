#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/vector_class.hpp"
#include "shared/mplayer_score_type.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/crt_string.hpp"
void __fastcall Collect_Coop_Player_Score_0048e210(MPlayerScoreType &output, bool skip_first);
char *__fastcall Unknown_006FA120(unsigned short const *string);
// @ref ?Collect_Coop_Player_Score_0048e210@@YIXAAVMPlayerScoreType@@_N@Z=0048e210
// @ref ?Unknown_006FA120@@YIPADPBG@Z=006fa120
bool CoopCampaignClass::Get_Player_Scores_0048e710(DynamicVectorClass<MPlayerScoreType *> &scores, int *time)
{
    if(!Initialized) return false;
    while(scores.Count()!=0) {
        delete scores[0];
        scores.Delete(0);
    }
    MPlayerScoreType *first=new MPlayerScoreType;
    Collect_Coop_Player_Score_0048e210(*first,false);
    MPlayerScoreType *second=new MPlayerScoreType;
    Collect_Coop_Player_Score_0048e210(*second,true);
    if(strcmp(FirstName,Unknown_006FA120(first->Name))!=0) {
        MPlayerScoreType *temp=first;
        first=second;
        second=temp;
    }
    for(int i=0;i<2;++i) {
        MPlayerScoreType *score=i==0 ? first : second;
        score->Kills=Kills[i];
        score->Built=Built[i];
        score->Lost=Lost[i];
        score->Winner=CurrentMap;
        score->Score=Score[i];
        scores.Add(score);
    }
    *time=Time;
    return true;
}
