// bool MPCooperative::unknown_slot36() -- 0x005A5350
// Shows the score screen for the map just played (making it on first use); returns what the
// screen left in unknown_score_850504.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
// @ref ?unknown_score_850504@@3_NA=00850504
// @ref ?unknown_empty_wide_839d4c@@3QBGB=00839d4c
// @ref ??_7?$VectorClass@PAVMPlayerScoreType@@@@6B@=007a68c4
// @ref ??_7?$DynamicVectorClass@PAVMPlayerScoreType@@@@6B@=007a68e4
// @ref ??_E?$VectorClass@PAVMPlayerScoreType@@@@UAEPAXI@Z=005a6bf0
// @ref ??_G?$VectorClass@PAVMPlayerScoreType@@@@UAEPAXI@Z=005a6bf0
// @ref ??_E?$DynamicVectorClass@PAVMPlayerScoreType@@@@UAEPAXI@Z=005a6360
// @ref ??_G?$DynamicVectorClass@PAVMPlayerScoreType@@@@UAEPAXI@Z=005a6360
// @ref ??0?$VectorClass@PAVMPlayerScoreType@@@@QAE@IPBQAVMPlayerScoreType@@@Z=005a6d80
// @ref ??0?$DynamicVectorClass@PAVMPlayerScoreType@@@@QAE@ABV0@@Z=005a62d0
// @ref ??0CampaignScoreClass@@QAE@XZ=00465bf0
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/unknown_description_list.hpp"
#include "shared/campaign_score.hpp"
#include "shared/abstract_type.hpp"
#include "shared/id_source.hpp"

bool MPCooperative::unknown_slot36()
{
    if (unknown_score_54 == 0) {
        unknown_score_54 = new CampaignScoreClass();
    }
    if (unknown_campaign_44 == 0) {
        return false;
    }
    if (unknown_campaigns_40 == 0) {
        return false;
    }
    DynamicVectorClass<MPlayerScoreType *> scores;
    int time;
    unknown_campaign_44->Get_Player_Scores_0048e710(scores, &time);
    UnknownDescriptionRecord_00490E00 *record = 0;
    int type;
    if (!unknown_campaign_44->Get_Campaign_Type_0048e6b0(&type)) {
        type = -1;
    } else {
        unknown_campaigns_40->Get_Record_00490C50(type, &record);
    }
    int difficulty = -1;
    if (type == 0 || type == 1) {
        difficulty = 0;
    } else if (type == 2 || type == 3) {
        difficulty = 1;
    } else if (type == 4) {
        difficulty = 2;
    }
    int count;
    unknown_campaign_44->Get_Map_Count_0048e6d0(&count);
    int current;
    unknown_campaign_44->Get_Current_Map_0048e6f0(&current);
    if (record != 0) {
        unknown_score_54->Presentation(scores, unknown_id_source_a3d290->ElapsedTime.Time(), current < count, difficulty, record->Name);
    } else {
        unknown_score_54->Presentation(scores, unknown_id_source_a3d290->ElapsedTime.Time(), current < count, difficulty, unknown_empty_wide_839d4c);
    }
    while (scores.Count() != 0) {
        if (scores[0] != 0) {
            delete scores[0];
        }
        scores[0] = 0;
        scores.Delete(0);
    }
    bool result = unknown_score_850504;
    unknown_score_850504 = false;
    return result;
}
