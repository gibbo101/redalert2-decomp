#include "shared/reference_counted.hpp"
namespace WorldDominationTour { class Campaign; }
extern rc_ptr<WorldDominationTour::Campaign> current_campaign_00b2ad78;
// @ref ?current_campaign_00b2ad78@@3V?$rc_ptr@VCampaign@WorldDominationTour@@@@A=00b2ad78
rc_ptr<WorldDominationTour::Campaign> const &__fastcall Current_WDT_Campaign_00769670()
{
    return current_campaign_00b2ad78;
}
