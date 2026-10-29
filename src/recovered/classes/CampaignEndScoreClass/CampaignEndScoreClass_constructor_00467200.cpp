// CampaignEndScoreClass::CampaignEndScoreClass() -- 0x00467200
// Clears the end screen's difficulty (-1: unknown), score count and time.
// @ref ??_7CampaignEndScoreClass@@6B@=0079d730
// @ref ?unknown_end_score_count_8504e8@@3HA=008504e8
// @ref ?unknown_end_score_time_85049c@@3HA=0085049c
// @ref ?unknown_end_score_difficulty_8504d0@@3HA=008504d0
#include "shared/campaign_score.hpp"

CampaignEndScoreClass::CampaignEndScoreClass()
{
    unknown_end_score_difficulty_8504d0 = -1;
    unknown_end_score_count_8504e8 = 0;
    unknown_end_score_time_85049c = 0;
}
