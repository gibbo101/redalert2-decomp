// rc_ptr<Campaign> __fastcall WorldDominationTour::Campaign::Create(Wstring const &name, rc_ptr<CampaignProperties> const &properties) (0x00725EE0)
// A new campaign, returned counted; empty without properties.
#include "shared/wdt_campaign.hpp"

namespace WorldDominationTour {

rc_ptr<Campaign> __fastcall Campaign::Create(Wstring const &name, rc_ptr<CampaignProperties> const &properties)
{
    if (!properties.Get()) {
        return rc_ptr<Campaign>();
    }
    return rc_ptr<Campaign>(new Campaign(name, properties));
}

}
