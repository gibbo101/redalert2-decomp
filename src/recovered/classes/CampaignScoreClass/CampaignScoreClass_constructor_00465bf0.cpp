// CampaignScoreClass::CampaignScoreClass() -- 0x00465BF0
// Clears the score screen's field and the shown map's time and difficulty (-1: unknown).
// @ref ??_7CampaignScoreClass@@6B@=0079d724
// @ref ?unknown_score_time_850508@@3HA=00850508
// @ref ?unknown_score_difficulty_7d1480@@3HA=007d1480
#include "shared/campaign_score.hpp"

CampaignScoreClass::CampaignScoreClass()
{
    unknown_04 = 0;
    unknown_score_time_850508 = 0;
    unknown_score_difficulty_7d1480 = -1;
}
