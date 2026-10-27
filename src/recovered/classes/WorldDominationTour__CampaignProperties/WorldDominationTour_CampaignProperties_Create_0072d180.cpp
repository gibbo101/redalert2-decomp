// rc_ptr<CampaignProperties> __fastcall WorldDominationTour::CampaignProperties::Create(rc_ptr<WDTState> const &wdt_state) (0x0072D180)
#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

rc_ptr<CampaignProperties> __fastcall CampaignProperties::Create(rc_ptr<WDTState> const &wdt_state)
{
    return rc_ptr<CampaignProperties>(new CampaignProperties(wdt_state));
}

}
