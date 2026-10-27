// ??1CampaignClass@@UAE@XZ (0x00465500)
// Detaches the campaign and unlists it.
#include "shared/campaign.hpp"
// @ref ?Detach_This_From_All@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ??1AbstractTypeClass@@UAE@XZ=00410740

CampaignClass::~CampaignClass()
{
    Detach_This_From_All(this, true);
    Campaigns.Delete(this);
}
